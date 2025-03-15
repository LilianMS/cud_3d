#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> //printf
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# define WIDTH 1024 // tamanho da tela
# define HEIGHT 512

typedef struct s_cub3d {
	int			*map; //esse array de mapa está em 1D, para mapas não convexos vamos precisar de outra solução
	int			map_width;
	int			map_height;
	int			tile_size;
	int			**matrix;
	mlx_t		*mlx;
	mlx_image_t	*img;
	float		player_x;
	float		player_y;
	float		player_angle;
	bool		keys[512];
}	t_cub3d;

//mlx_utils.c
void	initialize_mlx(t_cub3d *mapdata);

//map.c
void	init_map(t_cub3d *mapdata);
void	draw_minimap (t_cub3d *mapdata);

//main.c
void	ft_error(void);

//movement.c
void	deal_key(struct mlx_key_data keydata, void *param);
void	handle_movement(t_cub3d *mapdata);

#endif