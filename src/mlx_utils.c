#include "cub3d.h"
#include <stdint.h> //para uint32_t

static void clear_minimap_area(t_cub3d *mapdata)
{
	int x;
	int y;
	int color;
	int width;
	int height;

	color = 0x333333FF;
	width = MINIMAP_OFFSET_X + (mapdata->map_width * mapdata->tile_size);
	height = MINIMAP_OFFSET_Y + (mapdata->map_height * mapdata->tile_size);
	y = MINIMAP_OFFSET_Y;
	while (y < height)
	{
		x = MINIMAP_OFFSET_X;
		while (x < width)
		{
			mlx_put_pixel(mapdata->img, x, y, color);
			x++;
		}
		y++;
	}
}


static void	render_player(t_cub3d *mapdata)
{
	int	dx;
	int	dy;
	int	px;
	int	py;
	int	player_size;

	player_size = mapdata->tile_size / 8;
	dy = -player_size;
	while (dy <= player_size)
	{
		dx = -player_size;
		while (dx <= player_size)
		{
			px = MINIMAP_OFFSET_X + (int)(mapdata->player_x + dx);
			py = MINIMAP_OFFSET_Y + (int)(mapdata->player_y + dy);
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
				mlx_put_pixel(mapdata->img, px, py, 0xFFFF00FF);
			dx++;
		}
		dy++;
	}
}

//atualização a direção e renderiza seu vetor
static void	render_direction(t_cub3d *mapdata)
{
	float	dir_x;
	float	dir_y;
	int		i;
	int		px;
	int		py;

	dir_x = cos(mapdata->player_angle);
	dir_y = sin(mapdata->player_angle);
	i = 0;
	while (i < 20)
	{
		px = MINIMAP_OFFSET_X + (int)(mapdata->player_x + dir_x * i);
		py = MINIMAP_OFFSET_Y + (int)(mapdata->player_y - dir_y * i);
		if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
			mlx_put_pixel(mapdata->img, px, py, 0xFFA500FF);
		i++;
	}
}

static void	render(void *param)
{
	t_cub3d	*mapdata;

	mapdata = (t_cub3d *)param;
	handle_movement(mapdata);
	render_3d(mapdata);
	clear_minimap_area(mapdata);
	//fill_gray(mapdata->img);
	draw_minimap(mapdata);
	render_player(mapdata);
	render_direction(mapdata);
}

void	initialize_mlx(t_cub3d *mapdata)
{
	mlx_image_t	*img;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mapdata->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mapdata->mlx)
		cub_error(mlx_strerror(mlx_errno), mapdata);
	img = mlx_new_image(mapdata->mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mapdata->mlx, img, 0, 0) < 0))
		cub_error(mlx_strerror(mlx_errno), mapdata);
	mapdata->img = img;
	mlx_key_hook(mapdata->mlx, deal_key, mapdata);
	mlx_loop_hook(mapdata->mlx, &render, mapdata);
	mlx_loop(mapdata->mlx);
	mlx_terminate(mapdata->mlx);
}
