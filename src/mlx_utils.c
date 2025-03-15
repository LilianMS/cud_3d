#include "cub3d.h"
#include <stdint.h> //para uint32_t

static void	fill_gray(mlx_image_t *img) //função temporária para pintar o background do minimapa de cinza
{
	int			x;
	int			y;
	uint32_t	gray_color;

	gray_color = 0x888888FF;
	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, gray_color);
			x++;
		}
		y++;
	}
}

static void render_player(t_cub3d *mapdata)
{
	int dx;
	int dy;

	dy = -3;
	while (dy <= 3)
	{
		dx = -3;
		while (dx <= 3)
		{
			mlx_put_pixel(mapdata->img,
				(int)(mapdata->player_x + dx),
				(int)(mapdata->player_y + dy),
				0xFFFF00FF);
			dx++;
		}
		dy++;
	}
}

static void render_direction(t_cub3d *mapdata)
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
		px = (int)(mapdata->player_x + dir_x * i);
		py = (int)(mapdata->player_y + dir_y * i);
		mlx_put_pixel(mapdata->img, px, py, 0xFFA500FF);
		i++;
	}
}

static void render(void *param)
{
	t_cub3d *mapdata;

	mapdata = (t_cub3d *)param;
	handle_movement(mapdata);
	fill_gray(mapdata->img);
	draw_minimap(mapdata);
	render_player(mapdata);
	render_direction(mapdata);
}

void initialize_mlx(t_cub3d *mapdata)
{
	mlx_image_t *img;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mapdata->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mapdata->mlx)
		ft_error();
	img = mlx_new_image(mapdata->mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mapdata->mlx, img, 0, 0) < 0))
		ft_error();
	mapdata->img = img;
	init_map(mapdata); // função que seta o mapa
	mapdata->player_x = WIDTH / 4.0f;
	mapdata->player_y = HEIGHT / 2.0f;
	mapdata->player_angle = 0.0f; // Ângulo inicial
	mlx_key_hook(mapdata->mlx, deal_key, mapdata);
	mlx_loop_hook(mapdata->mlx, &render, mapdata);
	mlx_loop(mapdata->mlx);
	mlx_terminate(mapdata->mlx);
}
