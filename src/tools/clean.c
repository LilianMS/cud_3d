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

void	cub_free_data(t_cub3d *mapdata)
{
	if (mapdata->texture.north)
		mlx_delete_texture(mapdata->texture.north);
	if (mapdata->texture.south)
		mlx_delete_texture(mapdata->texture.south);
	if (mapdata->texture.west)
		mlx_delete_texture(mapdata->texture.west);
	if (mapdata->texture.east)
		mlx_delete_texture(mapdata->texture.east);
	if (mapdata->texture.no)
		free(mapdata->texture.no);
	if (mapdata->texture.so)
		free(mapdata->texture.so);
	if (mapdata->texture.we)
		free(mapdata->texture.we);
	if (mapdata->texture.ea)
		free(mapdata->texture.ea);
	if (mapdata->mapping.f_color)
		free_area(mapdata->mapping.f_color);
	if (mapdata->mapping.c_color)
		free_area(mapdata->mapping.c_color);
}

void	cub_clean(t_cub3d *mapdata)
{
	cub_free_data(mapdata);
	if (mapdata->flood_map)
		free_area(mapdata->flood_map);
	if (mapdata->mapping.area)
		free_area(mapdata->mapping.area);
	if (mapdata->map)
		free_area(mapdata->map);
	if (mapdata)
		free(mapdata);
}

int	ft_tern_op(int condition, int true_value, int false_value)
{
	if (condition)
		return true_value;
	else
		return false_value;
}
