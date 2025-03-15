#include "cub3d.h"

void	ft_error(void)
{
	fprintf(stderr, "%s\n", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_cub3d	*mapdata;

	(void)argc;
	(void)argv;
	// verificar argumentos
	mapdata = malloc(sizeof(t_cub3d));
	if (!mapdata)
		return (1);
	// verificar requisitos de mapa (mapa fechado)
	// popular matriz de mapa
	// verificar população de mapa
	initialize_mlx(mapdata);
	//liberação de memória
	free(mapdata);
	return (0);
}
