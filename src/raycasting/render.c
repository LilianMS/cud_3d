#include "cub3d.h"

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
