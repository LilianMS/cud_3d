#include "cub3d.h"

void	cub_error(const char *str, t_cub3d *mapdata)
{
	ft_putstr_fd("Error!\n", 2);
	ft_putstr_fd((char *)str, 2);
	ft_putstr_fd("\n", 2);
	cub_clean(mapdata);
	exit(EXIT_FAILURE);
}

