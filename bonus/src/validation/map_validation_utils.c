#include "cub3d.h"

void	cub_flood_fill(t_cub3d *mdata, t_pos pos)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= mdata->map_height \
		|| pos.x >= mdata->map_width)
		return ;
	if (mdata->flood_map[pos.y][pos.x] == '1' \
		|| mdata->flood_map[pos.y][pos.x] == 'T')
		return ;
	if (mdata->flood_map[pos.y][pos.x] == '0')
		mdata->flood_map[pos.y][pos.x] = 'T';
	cub_flood_fill(mdata, (t_pos){pos.x + 1, pos.y});
	cub_flood_fill(mdata, (t_pos){pos.x - 1, pos.y});
	cub_flood_fill(mdata, (t_pos){pos.x, pos.y + 1});
	cub_flood_fill(mdata, (t_pos){pos.x, pos.y - 1});
}

void	copy_map(t_cub3d *mdata)
{
	int	i;

	mdata->flood_map = malloc(sizeof(char *) * (mdata->map_height + 1));
	if (!mdata->flood_map)
		cub_error("Memory allocation failed!", mdata);
	i = 0;
	while (i < mdata->map_height)
	{
		mdata->flood_map[i] = ft_strdup(mdata->map[i]);
		if (!mdata->flood_map[i])
			cub_error("Memory allocation failed!", mdata);
		i++;
	}
	mdata->flood_map[mdata->map_height] = NULL;
}
