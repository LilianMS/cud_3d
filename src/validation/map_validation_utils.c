#include "cub3d.h"

void	cub_flood_fill(t_cub3d *mapdata, t_pos pos)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= mapdata->map_height \
		|| pos.x >= mapdata->map_width)
		return ;
	if (mapdata->flood_map[pos.y][pos.x] == '1' \
		|| mapdata->flood_map[pos.y][pos.x] == 'T')
		return ;
	if (mapdata->flood_map[pos.y][pos.x] == '0')
		mapdata->flood_map[pos.y][pos.x] = 'T';
	cub_flood_fill(mapdata, (t_pos){pos.x + 1, pos.y});
	cub_flood_fill(mapdata, (t_pos){pos.x - 1, pos.y});
	cub_flood_fill(mapdata, (t_pos){pos.x, pos.y + 1});
	cub_flood_fill(mapdata, (t_pos){pos.x, pos.y - 1});
}

void	copy_map(t_cub3d *mapdata)
{
	int	i;

	mapdata->flood_map = malloc(sizeof(char *) * (mapdata->map_height + 1));
	if (!mapdata->flood_map)
		cub_error("Memory allocation failed!", mapdata);
	i = 0;
	while (i < mapdata->map_height)
	{
		mapdata->flood_map[i] = ft_strdup(mapdata->map[i]);
		if (!mapdata->flood_map[i])
			cub_error("Memory allocation failed!", mapdata);
		i++;
	}
	mapdata->flood_map[mapdata->map_height] = NULL;
}
