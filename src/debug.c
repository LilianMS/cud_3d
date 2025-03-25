#include "cub3d.h"

void	print_area(char **area)
{
	int	i;

	i = 0;
	while (area[i])
	{
		ft_putstr_fd(area[i], 1);
		// ft_putstr_fd("\n", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

void print_textures(t_cub3d *mapdata)
{
	ft_putendl_fd(mapdata->texture.no, 1);
	ft_putendl_fd(mapdata->texture.so, 1);
	ft_putendl_fd(mapdata->texture.we, 1);
	ft_putendl_fd(mapdata->texture.ea, 1);
}


