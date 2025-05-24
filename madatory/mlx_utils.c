#include "cub3d.h"

static void	render(void *param)
{
	t_cub3d	*mdata;

	mdata = (t_cub3d *)param;
	handle_movement(mdata);
	cub_render_3d(mdata);
}

void	initialize_mlx(t_cub3d *mdata)
{
	mlx_image_t	*img;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mdata->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mdata->mlx)
		cub_error(mlx_strerror(mlx_errno), mdata);
	img = mlx_new_image(mdata->mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mdata->mlx, img, 0, 0) < 0))
		cub_error(mlx_strerror(mlx_errno), mdata);
	mdata->img = img;
	mlx_key_hook(mdata->mlx, deal_key, mdata);
	mlx_loop_hook(mdata->mlx, &render, mdata);
	mlx_loop(mdata->mlx);
	mlx_terminate(mdata->mlx);
}
