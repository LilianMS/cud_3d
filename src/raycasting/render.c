#include "cub3d.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void	get_texture_point(t_cub3d *game)
{
	game->render.texture_x = (int)(game->render.wall_point * game->texture.curr->width);
	if ((game->render.side == 0 && game->render.ray_dir_x < 0) || (game->render.side == 1 && game->render.ray_dir_y > 0))
		game->render.texture_x = game->texture.curr->width - game->render.texture_x - 1;
	game->render.resize = 1.0 * game->texture.curr->height / game->render.line_height;
}

void	set_wall_point(t_cub3d *game)
{
	double	wall_point;

	if (game->render.side == 0)
	{
		wall_point = (game->player_y / game->tile_size) + game->render.perp_wall_dist
			* game->render.ray_dir_y;
	}
	else
	{
		wall_point = (game->player_x / game->tile_size) + game->render.perp_wall_dist
			* game->render.ray_dir_x;
	}
	game->render.wall_point = wall_point - floor(wall_point);
}

void	capture_texture(t_cub3d *game)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (game->render.side == 1)
	{
		if (game->render.step_y < 0)
			texture = game->texture.north;
		else
			texture = game->texture.south;
	}
	else
	{
		if (game->render.step_x < 0)
			texture = game->texture.west;
		else
			texture = game->texture.east;
	}
	game->texture.curr = texture;
}

static void	clear_3d_render(t_cub3d *mapdata)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(mapdata->img, x, y, mapdata->mapping.c_color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(mapdata->img, x, y, mapdata->mapping.f_color);
			x++;
		}
		y++;
	}
}

static void	calculate_delta_distances(t_cub3d *mapdata)
{
	if (mapdata->render.ray_dir_x == 0)
		mapdata->render.delta_dist_x = VERY_BIG;
	else
		mapdata->render.delta_dist_x = fabs(1.0 / mapdata->render.ray_dir_x);
	if (mapdata->render.ray_dir_y == 0)
		mapdata->render.delta_dist_y = VERY_BIG;
	else
		mapdata->render.delta_dist_y = fabs(1.0 / mapdata->render.ray_dir_y);
}

static double	calculate_side_distance(double player_pos, int map_pos, \
				double delta_dist, double ray_dir)
{
	if (ray_dir < 0)
		return ((player_pos - map_pos) * delta_dist);
	else
		return ((map_pos + 1.0 - player_pos) * delta_dist);
}

static void	initialize_ray_steps(t_cub3d *mapdata)
{
	mapdata->render.step_x = ft_tern_op(mapdata->render.ray_dir_x < 0, -1, 1);
	mapdata->render.step_y = ft_tern_op(mapdata->render.ray_dir_y < 0, -1, 1);
	mapdata->render.side_dist_x = calculate_side_distance(
			mapdata->player_x / mapdata->tile_size,
			mapdata->render.map_x,
			mapdata->render.delta_dist_x,
			mapdata->render.ray_dir_x
			);
	mapdata->render.side_dist_y = calculate_side_distance(
			mapdata->player_y / mapdata->tile_size,
			mapdata->render.map_y,
			mapdata->render.delta_dist_y,
			mapdata->render.ray_dir_y
			);
}

static void	perform_dda(t_cub3d *mapdata, int *hit)
{
	while (!(*hit))
	{
		if (mapdata->render.side_dist_x < mapdata->render.side_dist_y)
		{
			mapdata->render.side_dist_x += mapdata->render.delta_dist_x;
			mapdata->render.map_x += mapdata->render.step_x;
			mapdata->render.side = 0;
		}
		else
		{
			mapdata->render.side_dist_y += mapdata->render.delta_dist_y;
			mapdata->render.map_y += mapdata->render.step_y;
			mapdata->render.side = 1;
		}
		if (mapdata->render.map_y < 0 \
			|| mapdata->render.map_y >= mapdata->map_height \
			|| mapdata->render.map_x < 0 \
			|| mapdata->render.map_x >= mapdata->map_width)
			*hit = 1;
		else if (mapdata-> \
				map[mapdata->render.map_y][mapdata->render.map_x] == '1')
			*hit = 1;
	}
}

static void	cast_single_ray(t_cub3d *mapdata)
{
	int	hit;

	mapdata->render.ray_dir_x = cos(mapdata->render.ray_angle);
	mapdata->render.ray_dir_y = -sin(mapdata->render.ray_angle);
	mapdata->render.map_x = (int)(mapdata->player_x / mapdata->tile_size);
	mapdata->render.map_y = (int)(mapdata->player_y / mapdata->tile_size);
	calculate_delta_distances(mapdata);
	initialize_ray_steps(mapdata);
	hit = 0;
	perform_dda(mapdata, &hit);
	if (mapdata->render.side == 0)
		mapdata->render.perp_wall_dist = (mapdata->render.map_x \
				- (mapdata->player_x / mapdata->tile_size) \
				+ (1 - mapdata->render.step_x) / 2.0) / mapdata->render.ray_dir_x;
	else
		mapdata->render.perp_wall_dist = (mapdata->render.map_y \
				- (mapdata->player_y / mapdata->tile_size) \
				+ (1 - mapdata->render.step_y) / 2.0) / mapdata->render.ray_dir_y;
	if (mapdata->render.perp_wall_dist < 0.0001)
		mapdata->render.perp_wall_dist = 0.0001;
}

// static void	draw_column_slice(t_cub3d *mapdata, int x)
// {
// 	int	y;

// 	mapdata->render.line_height = 
// 			(int)(HEIGHT / mapdata->render.perp_wall_dist);
// 	mapdata->render.draw_start = 
// 			(-mapdata->render.line_height / 2) + (HEIGHT / 2);
// 	mapdata->render.draw_end = (mapdata->render.line_height / 2) + (HEIGHT / 2);
// 	if (mapdata->render.draw_start < 0)
// 		mapdata->render.draw_start = 0;
// 	if (mapdata->render.draw_end >= HEIGHT)
// 		mapdata->render.draw_end = HEIGHT - 1;
// 	mapdata->render.wall_color = 0xFFFF00FF;
// 	if (mapdata->render.side == 1)
// 		mapdata->render.wall_color = 0xFFAA00FF;
// 	y = mapdata->render.draw_start;
// 	while (y < mapdata->render.draw_end)
// 	{
// 		mlx_put_pixel(mapdata->img, x, y, mapdata->render.wall_color);
// 		y++;
// 	}
// }

uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	int		texture_pos;
	uint8_t	*pixel;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	texture_pos = y * texture->width + x;
	texture_pos *= texture->bytes_per_pixel;
	pixel = &texture->pixels[texture_pos];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

static void	draw_column_slice(t_cub3d *mapdata, int x)
{
	int		y;
	int		tex_y;
	uint32_t	color;

	mapdata->render.line_height = (int)(HEIGHT / mapdata->render.perp_wall_dist);
	mapdata->render.draw_start = -mapdata->render.line_height / 2 + HEIGHT / 2;
	mapdata->render.draw_end = mapdata->render.line_height / 2 + HEIGHT / 2;

	if (mapdata->render.draw_start < 0)
		mapdata->render.draw_start = 0;
	if (mapdata->render.draw_end >= HEIGHT)
		mapdata->render.draw_end = HEIGHT - 1;

	// Captura a textura correta para a parede (norte, sul, leste, oeste)
	capture_texture(mapdata);
	// Calcula a posição X da textura
	set_wall_point(mapdata);
	get_texture_point(mapdata);
	mapdata->render.texture_pos = (mapdata->render.draw_start - HEIGHT / 2 + mapdata->render.line_height / 2) * mapdata->render.resize;
	y = mapdata->render.draw_start;
	while (y < mapdata->render.draw_end)
	{
		// Calcula a posição Y correspondente na textura
		tex_y = (int)mapdata->render.texture_pos;
		if(tex_y < 0)
			tex_y = 0;
		if(tex_y >= (int)mapdata->texture.curr->height)
			tex_y = (int)mapdata->texture.curr->height - 1;
		mapdata->render.texture_pos += mapdata->render.resize;
		// Pega a cor da textura
		color = get_texture_pixel(mapdata->texture.curr, mapdata->render.texture_x, tex_y);
		// Desenha o pixel no framebuffer
		mlx_put_pixel(mapdata->img, x, y, color);
		y++;
	}
}



void	render_3d(t_cub3d *mapdata)
{
	int	x;

	clear_3d_render(mapdata);
	x = 0;
	while (x < WIDTH)
	{
		mapdata->render.camera_x = 2.0 * x / (double)WIDTH - 1.0;
		mapdata->render.ray_angle = mapdata->player_angle \
								- mapdata->render.camera_x * (FOV / 2.0);
		cast_single_ray(mapdata);
		draw_column_slice(mapdata, x);
		x++;
	}
}
