#include "cub3d.h"
#include <stdio.h> //debug

void	cub_load_textures(t_cub3d *mdata)
{
	mdata->texture.north = mlx_load_png(mdata->texture.no);
	if (!mdata->texture.north)
		cub_error("Error loading north texture!", mdata);
	mdata->texture.south = mlx_load_png(mdata->texture.so);
	if (!mdata->texture.south)
		cub_error("Error loading south texture!", mdata);
	mdata->texture.west = mlx_load_png(mdata->texture.we);
	if (!mdata->texture.west)
		cub_error("Error loading west texture!", mdata);
	mdata->texture.east = mlx_load_png(mdata->texture.ea);
	if (!mdata->texture.east)
		cub_error("Error loading east texture!", mdata);
}

int	cub_starts(char **av, t_cub3d *mdata)
{
	if (!mdata)
		cub_error("Memory allocation error.", NULL);
	ft_memset(mdata, 0, sizeof(t_cub3d)); //inicializar a struct
	mdata->mapping.file = av[1];
	cub_valid(mdata); // validação completa
	cub_load_textures(mdata); // carrega as texturas
	//////////////////////// --- debug
	print_area(mdata->map);
	printf("Player pos: (%.1f, %.1f), angle: %.2f\n", mdata->player_x, mdata->player_y, mdata->player_angle);
	printf("Map size: %d x %d\n", mdata->map_width, mdata->map_height);
	////////////////////////end debug
	mdata->fov = M_PI / 3.0; // Exemplo: 60 graus em radianos
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	*mdata;

	if (ac != 2)
		cub_error("Argument with 'file.cub' is required!", NULL);
	mdata = malloc(sizeof(t_cub3d));
	cub_starts(av, mdata);
	initialize_mlx(mdata);
	cub_clean(mdata);
	return (0);
}

// para rodar com valgrind e supressions:
// valgrind --suppressions=mlx42.supp  ./cub3D assets/map/simple_map.cub
// mais completo: valgrind --leak-check=full --show-leak-kinds=all --suppressions=mlx42.supp ./cub3D assets/map/simple_map.cub
