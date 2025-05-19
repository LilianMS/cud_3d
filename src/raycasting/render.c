#include "cub3d.h"

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
	// deltaDistX / deltaDistY
	if (mapdata->render.rayDirX == 0)
		mapdata->render.deltaDistX = VERY_BIG;
	else
		mapdata->render.deltaDistX = fabs(1.0 / mapdata->render.rayDirX);
	if (mapdata->render.rayDirY == 0)
		mapdata->render.deltaDistY = VERY_BIG;
	else
		mapdata->render.deltaDistY = fabs(1.0 / mapdata->render.rayDirY);
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
	mapdata->render.stepX = ft_tern_op(mapdata->render.rayDirX < 0, -1, 1);
	mapdata->render.stepY = ft_tern_op(mapdata->render.rayDirY < 0, -1, 1);
	mapdata->render.sideDistX = calculate_side_distance(
			mapdata->player_x / mapdata->tile_size,
			mapdata->render.mapX,
			mapdata->render.deltaDistX,
			mapdata->render.rayDirX
			);
	mapdata->render.sideDistY = calculate_side_distance(
			mapdata->player_y / mapdata->tile_size,
			mapdata->render.mapY,
			mapdata->render.deltaDistY,
			mapdata->render.rayDirY
			);
}

//DDA - descobre onde o raio bateu (e se vert ou hor) e retorna a distância perpendicular
static void	perform_dda(t_cub3d *mapdata, int *hit)
{
	while (!(*hit))
	{
		if (mapdata->render.sideDistX < mapdata->render.sideDistY)
		{
			mapdata->render.sideDistX += mapdata->render.deltaDistX;
			mapdata->render.mapX += mapdata->render.stepX;
			mapdata->render.side = 0;
		}
		else
		{
			mapdata->render.sideDistY += mapdata->render.deltaDistY;
			mapdata->render.mapY += mapdata->render.stepY;
			mapdata->render.side = 1;
		}
		if (mapdata->render.mapY < 0 \
			|| mapdata->render.mapY >= mapdata->map_height \
			|| mapdata->render.mapX < 0 \
			|| mapdata->render.mapX >= mapdata->map_width)
			*hit = 1; // saiu do mapa
		else if (mapdata-> \
				map[mapdata->render.mapY][mapdata->render.mapX] == '1')
			*hit = 1;
	}
}

static void	cast_single_ray(t_cub3d *mapdata)
{
	int	hit;

	mapdata->render.rayDirX = cos(mapdata->render.rayAngle);
	mapdata->render.rayDirY = -sin(mapdata->render.rayAngle);
	mapdata->render.mapX = (int)(mapdata->player_x / mapdata->tile_size);
	mapdata->render.mapY = (int)(mapdata->player_y / mapdata->tile_size);
	// deltaDistX, deltaDistY
	calculate_delta_distances(mapdata);
	// stepX, stepY, sideDistX, sideDistY
	initialize_ray_steps(mapdata);
	// DDA loop
	hit = 0;
	perform_dda(mapdata, &hit);
	// Distância perpendicular
	if (mapdata->render.side == 0)
		mapdata->render.perpWallDist = (mapdata->render.mapX \
				- (mapdata->player_x / mapdata->tile_size) \
				+ (1 - mapdata->render.stepX) / 2.0) / mapdata->render.rayDirX;
	else
		mapdata->render.perpWallDist = (mapdata->render.mapY \
				- (mapdata->player_y / mapdata->tile_size) \
				+ (1 - mapdata->render.stepY) / 2.0) / mapdata->render.rayDirY;
	if (mapdata->render.perpWallDist < 0.0001)
		mapdata->render.perpWallDist = 0.0001;
}

//faz o desenho de uma linha vertical
static void	draw_column_slice(t_cub3d *mapdata, int x)
{
	int	y;

	mapdata->render.lineHeight = \
			(int)(HEIGHT / mapdata->render.perpWallDist);
	mapdata->render.drawStart = \
			(-mapdata->render.lineHeight / 2) + (HEIGHT / 2);
	mapdata->render.drawEnd = (mapdata->render.lineHeight / 2) + (HEIGHT / 2);
	if (mapdata->render.drawStart < 0)
		mapdata->render.drawStart = 0;
	if (mapdata->render.drawEnd >= HEIGHT)
		mapdata->render.drawEnd = HEIGHT - 1;
	// Escolhe cor (diferente se horizontal ou vertical)
	mapdata->render.wallColor = 0xFFFF00FF; // amarelo
	if (mapdata->render.side == 1)
		mapdata->render.wallColor = 0xFFAA00FF; // laranja
	// Desenha pixel a pixel
	y = mapdata->render.drawStart;
	while (y < mapdata->render.drawEnd)
	{
		mlx_put_pixel(mapdata->img, x, y, mapdata->render.wallColor);
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
		mapdata->render.cameraX = 2.0 * x / (double)WIDTH - 1.0;
		mapdata->render.rayAngle = mapdata->player_angle \
								- mapdata->render.cameraX * (FOV / 2.0);
		cast_single_ray(mapdata);
		draw_column_slice(mapdata, x);
		x++;
	}
}
