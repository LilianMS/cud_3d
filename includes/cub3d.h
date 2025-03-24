#ifndef CUB3D_H
# define CUB3D_H

// # include <stdio.h> //printf
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h> //open
// # include <stdbool.h> 
# include "../lib/libft/includes/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# define WIDTH 1024 // tamanho da tela
# define HEIGHT 512

typedef struct s_cub3d
{
	char		*cub;
	char		**map;
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

// utils.c - funções de erro
void	cub_error(const char *str, t_cub3d *mapdata);
// void	free_map(t_cub3d *mapdata);

//validation.c - funções de validação de arquivo .cub
int		cub_valid(t_cub3d *mapdata);

//mlx_utils.c - inicialização de mlx e chamada de outras funções de renderização
void	initialize_mlx(t_cub3d *mapdata);

//map.c - inicialização de renderização do mapa (futuro minimapa)
void	init_map(t_cub3d *mapdata);
void	draw_minimap(t_cub3d *mapdata);
void	find_player_start(t_cub3d *mapdata);

//main.c
// void	ft_error(void);

//movement.c - funções de movimento e rotação
void	deal_key(struct mlx_key_data keydata, void *param);
void	handle_movement(t_cub3d *mapdata);

//wall.c - funções de colisão e movimentação junto à parede
int		is_wall(t_cub3d *mapdata, float x, float y);
void	wall_sliding(t_cub3d *mapdata, float dx, float dy);

#endif