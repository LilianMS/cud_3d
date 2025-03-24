#include "cub3d.h"

void	ft_error(void)
{
	fprintf(stderr, "%s\n", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	ax_main(t_cub3d *mapdata)
{
	// verificar argumentos
	
	// verificar requisitos de mapa (mapa fechado, precisa ter uma psoição inicial de player)
	// popular matriz de mapa
	// verificar população de mapa
	initialize_mlx(mapdata);
	//liberação de memória
	free(mapdata);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	*mapdata;

	if (ac != 2)
		cub_error("Argument with 'file.cub' is required!");
	mapdata = malloc(sizeof(t_cub3d));
	if (!mapdata)
		return (1);
	mapdata->cub = av[1];
	if (cub_valid(mapdata))
		ax_main(mapdata);
	return (0);
}