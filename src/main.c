#include "cub3d.h"

// void	ft_error(void)
// {
// 	fprintf(stderr, "%s\n", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

int	cub_starts(char **av, t_cub3d *mapdata)
{
	if (!mapdata)
		cub_error("Memory allocation error.", NULL);
	ft_memset(mapdata, 0, sizeof(t_cub3d)); //inicializar a struct
	mapdata->cub = av[1];
	cub_valid(mapdata);
	// verificar requisitos de mapa (mapa fechado, precisa ter uma psoição inicial de player)
	// popular matriz de mapa
	// verificar população de mapa
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	*mapdata;

	if (ac != 2)
		cub_error("Argument with 'file.cub' is required!", NULL);
	mapdata = malloc(sizeof(t_cub3d));
	cub_starts(av, mapdata);
	initialize_mlx(mapdata);
	free(mapdata);
	return (0);
}

// para rodar com valgrind e supressions:
// valgrind --suppressions=mlx42.supp  ./cub3D assets/map/simple_map.cub