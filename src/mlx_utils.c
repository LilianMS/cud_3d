#include "cub3d.h"
#include "minimap.h"

static void	render(void *param)
{
	double	current_time;
	double	delta_time;
	t_cub3d	*mdata;

	mdata = (t_cub3d *)param;
	current_time = mlx_get_time();
	delta_time = current_time - mdata->last_frame_time;
	mdata->last_frame_time = current_time;
	handle_movement(mdata);
	cub_render_3d(mdata);
}

void	initialize_mlx(t_cub3d *mdata)
{
	mlx_image_t	*img;

	mdata->last_frame_time = mlx_get_time();
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
}
