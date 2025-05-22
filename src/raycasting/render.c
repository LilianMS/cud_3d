#include "cub3d.h"

void	cub_render_3d(t_cub3d *mapdata)
{
	int	x;

	cub_clear_3d_render(mapdata);
	x = 0;
	while (x < WIDTH)
	{
		mapdata->render.camera_x = 2.0 * x / (double)WIDTH - 1.0;
		mapdata->render.ray_angle = mapdata->player_angle \
								- mapdata->render.camera_x \
								* (mapdata->fov / 2.0);
		cub_cast_single_ray(mapdata);
		cub_draw_column_slice(mapdata, x);
		x++;
	}
}
