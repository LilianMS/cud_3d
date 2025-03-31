#include "cub3d.h"

void	allocate_and_copy_map(t_cub3d *mapdata, int start, int map_lines)
{
	int	i;

	i = 0;
	mapdata->map = malloc(sizeof(char *) * (map_lines + 1));
	if (!mapdata->map)
		cub_error("Failed to allocate map", mapdata);
	while (i < map_lines)
	{
		mapdata->map[i] = ft_strdup(mapdata->mapping.area[start + i]);
		if (!mapdata->map[i])
			cub_error("Map line allocation failed", mapdata);
		i++;
	}
	mapdata->map[i] = NULL;
}

void	calculate_map_dimensions(t_cub3d *mapdata, int map_lines)
{
	int	i;
	int	len;

	i = 0;
	mapdata->map_height = map_lines;
	mapdata->map_width = 0;
	while (i < map_lines)
	{
		len = ft_strlen(mapdata->map[i]);
		if (len > mapdata->map_width)
			mapdata->map_width = len;
		i++;
	}
}
