#include "cub3d.h"
#include <stdint.h> //para uint32_t

void	deal_key(struct mlx_key_data keydata, void *param)
{
	t_cub3d	*mapdata;
	float	move_speed;

	move_speed = 5.0f; //ajustar velocidade do movimento
	mapdata = (t_cub3d *)param;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mapdata->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
			mapdata->player_y -= move_speed; // “W” move pra cima (diminuindo Y)
		if (keydata.key == MLX_KEY_S)
			mapdata->player_y += move_speed; // “S” move pra baixo
		if (keydata.key == MLX_KEY_A)
			mapdata->player_x -= move_speed; // “A” move à esquerda
		if (keydata.key == MLX_KEY_D)
			mapdata->player_x += move_speed; // “D” move à direita
	}
}

static void	fill_gray(mlx_image_t *img) //função temporária
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

void	ft_error(void)
{
	fprintf(stderr, "%s\n", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void render(void *param)
{
	t_cub3d	*mapdata;
	int		dx;
	int		dy;

	mapdata = (t_cub3d *)param;
	fill_gray(mapdata->img); // função temporária de fundo
	draw_minimap(mapdata);

	/*dx e dy nesse caso servem para aumentar a representação
	do jogador de apenas 1 pixel*/
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

void	initialize_mlx(t_cub3d *mapdata)
{
	mlx_image_t	*img;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mapdata->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mapdata->mlx)
		ft_error();
	img = mlx_new_image(mapdata->mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mapdata->mlx, img, 0, 0) < 0))
		ft_error();
	mapdata->img = img;
	init_map(mapdata); //futura função de carregar o mapa
	mapdata->player_x = WIDTH / 4.0f; //posição inicial do personagem
	mapdata->player_y = HEIGHT / 2.0f;
	mlx_key_hook(mapdata->mlx, deal_key, mapdata);
	mlx_loop_hook(mapdata->mlx, &render, mapdata);
	mlx_loop(mapdata->mlx);
	mlx_terminate(mapdata->mlx);
}
