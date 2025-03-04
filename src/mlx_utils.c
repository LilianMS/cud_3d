#include "cub3d.h"
#include <stdint.h> //para uint32_t

void	deal_key(struct mlx_key_data keydata, void *param)
{
	t_cub3d	*mapdata;

	mapdata = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mapdata->mlx);
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
	fill_gray(img); //temporário
	mlx_key_hook(mapdata->mlx, deal_key, mapdata);
	mlx_loop(mapdata->mlx);
	mlx_terminate(mapdata->mlx);
}