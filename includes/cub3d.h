#ifndef CUB3D_H
# define CUB3D_H

// # include <stdio.h> //printf
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h> //open
# include <math.h>
// # include <stdbool.h>
# include "../lib/libft/includes/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# define WIDTH 1024 // tamanho da tela
# define HEIGHT 768 // estava 512
# define MINIMAP_AREA_W   200
# define MINIMAP_AREA_H   200
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
# define FOV (M_PI / 3.0)
# define MAX_LINES 100
# define MAX_WIDTH 100
# define MIN_LINES 4
# define MIN_WIDTH 3
// / Valor grande para evitar divisão por zero.
# define VERY_BIG 1e30

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	char		*file;
	char		**area;
	uint32_t	f_color;
	uint32_t	c_color;
	// char	**map;
	int			lines;
	// int		cols;
}	t_map;

typedef struct s_texture
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*curr;
}	t_texture;

typedef struct s_render
{
	int		side;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	camera_x;
	double	ray_angle;
	double	perp_wall_dist;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	float		wall_point;
	int		texture_x;
	int		texture_y;
	float		texture_pos;
	float		resize;
	uint32_t		wall_color;

}	t_render;

typedef struct s_cub3d
{
	char		*tmp;
	char		**map;
	char		**flood_map; // cópia do mapa para o flood fill
	int			map_width;
	int			map_height;
	int			tile_size;
	int			**matrix;
	int			player_dir; // guarda o int char de nascimento ex: 'N'
	float		player_x;
	float		player_y;
	float		player_angle;
	bool		keys[512];
	t_pos		p_pos; // estrutura para guardar x e y (coordenadas, posição do jogador...)
	t_texture	texture; // path e carregamento das texturas
	t_map		mapping;
	t_render	render; // estrutura diminuir o numero de variaveis dentro das funçoes de render
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_cub3d;

// utils.c
void		cub_error(const char *str, t_cub3d *mapdata);
void		ft_remove_newline(char ***colors);
int				ft_array_len(char **array);
int			ft_if_surrounded_by_walls(char **area, t_pos pos, char wall);
int			ft_check_kind_file(char *str, char *suffix);
uint32_t	ft_rgb_to_int(int r, int g, int b);
int			ft_hash_table(const char *str, int *table);
void		ft_init_table(int *table, int size);
int			ft_str_is_space(const char *str);

//validations.c
int		cub_valid(t_cub3d *mapdata);

// validation_utils.c
int		cub_search_elements(t_cub3d *mapdata, const char *elements);
int		check_map_position(t_cub3d *mapdata, int end);

// check_chars.c
int		check_all_chars(char **area, const char *valid_chars);
int		cub_textures(t_cub3d *mapdata);

// check_elements.c
int		cub_colors(t_cub3d *mapdata);
void	ft_remove_end_spaces(char **str);

// map_validation.c
void	cub_player_validation(t_cub3d *mapdata, t_pos pos);
void	cub_map_validation(t_cub3d *mapdata, t_pos pos);

// map_validation_utils.c
void	cub_flood_fill(t_cub3d *mapdata, t_pos pos);
void	copy_map(t_cub3d *mapdata);

//mlx_utils.c - inicialização de mlx e chamada de outras funções de renderização
void	initialize_mlx(t_cub3d *mapdata);

//map_utils.c - funções adicionais para o mapa
void	cub_extract_map(t_cub3d *mapdata);
int		is_map_line(char *line);
int		calculate_tile_size(int map_width, int map_height);

// map_utils_2.c - + funções adicionais para o mapa
void	allocate_and_copy_map(t_cub3d *mapdata, int start, int map_lines, t_pos pos);

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

// clean.c
void	cub_clean(t_cub3d *mapdata);
void	free_area(char **area);
int		ft_tern_op(int condition, int true_value, int false_value);

//raycasting.c
void	render_3d(t_cub3d *mapdata);

//debug --- retirar funções de debug ao finalizar projeto
//   não esquecer de remover todos os comentários em português
void	print_area(char **area);
void	print_textures(t_cub3d *mapdata);

#endif
