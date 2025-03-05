#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*mapdata;

	(void)argc;
	(void)argv;
	// verificar argumentos
	// alocar memória para matriz de mapa (aqui está só placeholder)
	mapdata = malloc(sizeof(t_cub3d));
	if (!mapdata)
		return (1);
	// verificar requisitos de mapa (mapa fechado)
	// popular matriz de mapa
	// verificar população de mapa
	initialize_mlx(mapdata);
	//liberação de memória
	return (0);
}
