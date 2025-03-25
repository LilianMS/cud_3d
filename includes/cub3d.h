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
# define MAX_LINES 1024

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	char	*file;
	char	**area;
	char	**map;
	int		lines;
	int		cols;
}	t_map;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

}	t_texture;

typedef struct s_cub3d
{
	char		**map;
	int			map_width;
	int			map_height;
	int			tile_size;
	int			**matrix;
	float		player_x;
	float		player_y;
	float		player_angle;
	bool		keys[512];
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_texture	texture;
	t_map		mapping;
}	t_cub3d;

// utils.c 
void	cub_error(const char *str, t_cub3d *mapdata);
void	free_area(char **area);
// void	free_map(t_cub3d *mapdata);

//validation
int		cub_valid(t_cub3d *mapdata);
int		check_all_chars(char **area, const char *valid_chars);
int		search_elements(t_cub3d *mapdata, const char *elements);
int		cub_textures(t_cub3d *mapdata);

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


// clean
void	cub_clean(t_cub3d *mapdata);

//debug --- retirar funções de debug ao finalizar projeto
//   não esquecer de remover todos os comentários em português
void	print_area(char **area);
void	print_textures(t_cub3d *mapdata);


#endif