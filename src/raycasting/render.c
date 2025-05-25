#include "cub3d.h"

static void	get_texture_point(t_cub3d *mdata)
{
	mdata->render.texture_x = (int)(mdata->render.wall_point \
									* mdata->texture.curr->width);
	if ((mdata->render.side == 0 && mdata->render.ray_dir_x < 0) \
		|| (mdata->render.side == 1 && mdata->render.ray_dir_y > 0))
		mdata->render.texture_x = mdata->texture.curr->width \
									- mdata->render.texture_x - 1;
	mdata->render.resize = 1.0 * mdata->texture.curr->height \
			/ mdata->render.line_height;
}

static void	set_wall_point(t_cub3d *mdata)
{
	double	wall_point;

	if (mdata->render.side == 0)
	{
		wall_point = (mdata->player_y / mdata->tile_size) \
						+ mdata->render.perp_wall_dist
			* mdata->render.ray_dir_y;
	}
	else
	{
		wall_point = (mdata->player_x / mdata->tile_size) \
						+ mdata->render.perp_wall_dist
			* mdata->render.ray_dir_x;
	}
	mdata->render.wall_point = wall_point - floor(wall_point);
}

static void	draw_texture_slice(t_cub3d *mdata, int x)
{
	int			y;
	int			tex_y;
	uint32_t	color;

	y = mdata->render.draw_start;
	while (y < mdata->render.draw_end)
	{
		tex_y = (int)mdata->render.texture_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)mdata->texture.curr->height)
			tex_y = (int)mdata->texture.curr->height - 1;
		mdata->render.texture_pos += mdata->render.resize;
		color = cub_get_texture_pixel(mdata->texture.curr, \
				mdata->render.texture_x, tex_y);
		mlx_put_pixel(mdata->img, x, y, color);
		y++;
	}
}

void	cub_draw_column_slice(t_cub3d *mdata, int x)
{
	mdata->render.line_height = (int)(HEIGHT / mdata->render.perp_wall_dist);
	mdata->render.draw_start = -mdata->render.line_height / 2 + HEIGHT / 2;
	mdata->render.draw_end = mdata->render.line_height / 2 + HEIGHT / 2;
	if (mdata->render.draw_start < 0)
		mdata->render.draw_start = 0;
	if (mdata->render.draw_end >= HEIGHT)
		mdata->render.draw_end = HEIGHT - 1;
	cub_capture_texture(mdata);
	set_wall_point(mdata);
	get_texture_point(mdata);
	mdata->render.texture_pos = (mdata->render.draw_start - HEIGHT / 2 \
								+ mdata->render.line_height / 2) \
								* mdata->render.resize;
	draw_texture_slice(mdata, x);
}

void	cub_render_3d(t_cub3d *mdata)
{
	int	x;

	cub_clear_3d_render(mdata);
	x = 0;
	while (x < WIDTH)
	{
		mdata->render.camera_x = 2.0 * x / (double)WIDTH - 1.0;
		mdata->render.ray_angle = mdata->player_angle \
								- mdata->render.camera_x \
								* (mdata->fov / 2.0);
		cub_cast_single_ray(mdata);
		cub_draw_column_slice(mdata, x);
		x++;
	}
}
