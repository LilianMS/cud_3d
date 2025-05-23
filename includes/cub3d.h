#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include "../lib/libft/includes/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# define WIDTH 1024
# define HEIGHT 768
# define MINIMAP_AREA_W   200
# define MINIMAP_AREA_H   200
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define MAX_LINES 100
# define MAX_WIDTH 100
# define MIN_LINES 4
# define MIN_WIDTH 3
# define VERY_BIG 1e30

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	uint32_t	f_color;
	uint32_t	c_color;
	int			lines;
	char		**area;
	char		*file;
}	t_map;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*curr;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
}	t_texture;

typedef struct s_render
{
	double		camera_x;
	double		ray_angle;
	double		perp_wall_dist;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	float		wall_point;
	float		texture_pos;
	float		resize;
	uint32_t	wall_color;
	int			side;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			texture_x;
	int			texture_y;
}	t_render;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	char		*tmp;
	char		**map;
	char		**flood_map;
	int			**matrix;
	int			map_width;
	int			map_height;
	int			tile_size;
	float		player_x;
	float		player_y;
	float		player_angle;
	float		fov;
	int			player_dir;
	t_pos		p_pos;
	bool		keys[512];
	t_texture	texture;
	t_map		mapping;
	t_render	render;
}	t_cub3d;

// utils.c - Funções utilitárias gerais
void		cub_error(const char *str, t_cub3d *mdata);
void		ft_remove_newline(char ***colors);
void		ft_init_table(int *table, int size);
int			ft_array_len(char **array);
int			ft_if_surrounded_by_walls(char **area, t_pos pos, char wall);
int			ft_check_kind_file(char *str, char *suffix);
int			ft_hash_table(const char *str, int *table);
int			ft_str_is_space(const char *str);
int			ft_tern_op(int condition, int true_value, int false_value);
uint32_t	ft_rgb_to_int(int r, int g, int b);

// validations.c - Validação geral do mapa e elementos
int			cub_valid(t_cub3d *mdata);

// validation_utils.c - Funções auxiliares para validação
int			cub_search_elements(t_cub3d *mdata, const char *elements);
int			check_map_position(t_cub3d *mdata, int end);

// check_chars.c - Validação de caracteres no mapa
int			check_all_chars(char **area, const char *valid_chars);
int			cub_textures(t_cub3d *mdata);

// check_elements.c - Validação de cores e remoção de espaços
int			cub_colors(t_cub3d *mdata);
void		ft_remove_end_spaces(char **str);

// map_validation.c - Validação do jogador e do mapa
void		cub_player_validation(t_cub3d *mdata, t_pos pos);
void		cub_map_validation(t_cub3d *mdata, t_pos pos);

// map_validation_utils.c - Funções auxiliares para validação do mapa
void		cub_flood_fill(t_cub3d *mdata, t_pos pos);
void		copy_map(t_cub3d *mdata);

// mlx_utils.c - Inicialização do MLX e renderização
void		initialize_mlx(t_cub3d *mdata);

// map_utils.c - Funções auxiliares para manipulação do mapa
void		cub_extract_map(t_cub3d *mdata);
int			is_map_line(char *line);
int			calculate_tile_size(int map_width, int map_height);

// map_utils_2.c - Funções adicionais para manipulação do mapa
void		allocate_copy_map(t_cub3d *data, int init, int lines, t_pos pos);

// map.c - Inicialização e renderização do minimapa
void		init_map(t_cub3d *mdata);
void		draw_minimap(t_cub3d *mdata);
void		cub_player_start(t_cub3d *mdata);

// movement.c - Funções de movimentação e rotação
void		deal_key(struct mlx_key_data keydata, void *param);
void		handle_movement(t_cub3d *mdata);

// wall.c - Funções de colisão e movimentação junto à parede
int			is_wall(t_cub3d *mdata, float x, float y);
void		wall_sliding(t_cub3d *mdata, float dx, float dy);

// clean.c - Funções de limpeza de memória
void		cub_clean(t_cub3d *mdata);
void		free_area(char **area);

// raycasting.c - Renderização 3D
void		cub_render_3d(t_cub3d *mdata);
void		cub_cast_single_ray(t_cub3d *mdata);
void		cub_draw_column_slice(t_cub3d *mdata, int x);
void		cub_clear_3d_render(t_cub3d *mdata);
void		cub_capture_texture(t_cub3d *game);
uint32_t	cub_get_texture_pixel(mlx_texture_t *texture, int x, int y);

#endif
