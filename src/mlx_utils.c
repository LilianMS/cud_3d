#include "cub3d.h"

// void update_torch(void* param, double delta_time)
// {
//     t_cub3d *mdata = (t_cub3d *)param;
//     double frame_duration = 0.15;

//     mdata->anim.timer +=  delta_time;

//     if (mdata->anim.timer >= frame_duration)
//     {
//         mdata->anim.timer = 0;

//         // Desativa o frame atual
//         mdata->anim.torch_images[mdata->anim.torch_frame]->enabled = false;

//         // Vai para o próximo frame
//         mdata->anim.torch_frame = (mdata->anim.torch_frame + 1) % mdata->anim.torch_frame_count;

//         // Ativa o próximo frame
//         mdata->anim.torch_images[mdata->anim.torch_frame]->enabled = true;
//     }
// }

static void	render(void *param)
{
	t_cub3d	*mdata;

	mdata = (t_cub3d *)param;
	double current_time = mlx_get_time();
    double delta_time = current_time - mdata->last_frame_time;
    mdata->last_frame_time = current_time;

	handle_movement(mdata);
	cub_render_3d(mdata);
	update_animation(&mdata->anim.torch, delta_time);
	clear_minimap_area(mdata);
	draw_minimap(mdata);
	render_player(mdata);
	render_direction(mdata);
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
