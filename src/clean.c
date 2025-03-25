#include "cub3d.h"

void	free_area(char **area)
{
	int	i;

	i = 0;
	while (area[i])
	{
		free(area[i]);
		i++;
	}
	free(area);
}

void	free_textures(t_cub3d *mapdata)
{
	if (mapdata->texture.no)
		free(mapdata->texture.no);
	if (mapdata->texture.so)
		free(mapdata->texture.so);
	if (mapdata->texture.we)
		free(mapdata->texture.we);
	if (mapdata->texture.ea)
		free(mapdata->texture.ea);
}

void	cub_clean(t_cub3d *mapdata)
{
	free_textures(mapdata);
	if (mapdata->mapping.area)
		free_area(mapdata->mapping.area);
	if (mapdata)
		free(mapdata);
}
