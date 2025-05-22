#include "cub3d.h"
#include <stdio.h> //debug

void	cub_load_textures(t_cub3d *mapdata)
{
	mapdata->texture.north = mlx_load_png(mapdata->texture.no);
	if (!mapdata->texture.north)
		cub_error("Error loading north texture!", mapdata);
	mapdata->texture.south = mlx_load_png(mapdata->texture.so);
	if (!mapdata->texture.south)
		cub_error("Error loading south texture!", mapdata);
	mapdata->texture.west = mlx_load_png(mapdata->texture.we);
	if (!mapdata->texture.west)
		cub_error("Error loading west texture!", mapdata);
	mapdata->texture.east = mlx_load_png(mapdata->texture.ea);
	if (!mapdata->texture.east)
		cub_error("Error loading east texture!", mapdata);
}

int	cub_starts(char **av, t_cub3d *mapdata)
{
	if (!mapdata)
		cub_error("Memory allocation error.", NULL);
	ft_memset(mapdata, 0, sizeof(t_cub3d)); //inicializar a struct
	mapdata->mapping.file = av[1];
	cub_valid(mapdata); // validação completa
	cub_load_textures(mapdata); // carrega as texturas
	// --- debug
	print_area(mapdata->map);
	printf("Player pos: (%.1f, %.1f), angle: %.2f\n", mapdata->player_x, mapdata->player_y, mapdata->player_angle);
	printf("Map size: %d x %d\n", mapdata->map_width, mapdata->map_height);
	//end debug
	mapdata->fov = M_PI / 3.0; // Exemplo: 60 graus em radianos
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
	cub_clean(mapdata);
	return (0);
}

// para rodar com valgrind e supressions:
// valgrind --suppressions=mlx42.supp  ./cub3D assets/map/simple_map.cub
// mais completo: valgrind --leak-check=full --show-leak-kinds=all --suppressions=mlx42.supp ./cub3D assets/map/simple_map.cub
