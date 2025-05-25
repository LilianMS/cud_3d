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
	update_animation(&mdata->anim.torch, delta_time);
	if (mdata->minimap_visible)
	{
		mdata->minimap_static->enabled = true;
		mdata->minimap_dynamic->enabled = true;
		update_minimap_dynamic(mdata);
	}
	else
	{
		mdata->minimap_static->enabled = false;
		mdata->minimap_dynamic->enabled = false;
	}
}

void	mouse_hook(double xpos, \
				__attribute__((unused)) double ypos, void *param)
{
	t_cub3d			*mdata;
	static double	last_x = -1;
	double			delta_x;
	double			sensitivity;

	mdata = (t_cub3d *)param;
	if (mdata->minimap_visible)
		mlx_set_cursor_mode(mdata->mlx, MLX_MOUSE_NORMAL);
	else
		mlx_set_cursor_mode(mdata->mlx, MLX_MOUSE_DISABLED);
	if (last_x == -1)
		last_x = xpos;
	delta_x = xpos - last_x;
	last_x = xpos;
	sensitivity = 0.0025;
	mdata->player_angle -= delta_x * sensitivity;
	if (mdata->player_angle < 0)
		mdata->player_angle += 2 * M_PI;
	if (mdata->player_angle > 2 * M_PI)
		mdata->player_angle -= 2 * M_PI;
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
	mlx_set_cursor_mode(mdata->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(mdata->mlx, mouse_hook, mdata);
	mlx_key_hook(mdata->mlx, deal_key, mdata);
	mlx_loop_hook(mdata->mlx, &render, mdata);
}
