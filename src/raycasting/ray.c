#include "cub3d.h"

/*
** This file contains the implementation of raycasting for the cub3D 
** project. Raycasting is used to calculate the distance to walls and 
** render a 3D perspective based on a 2D map. The functions in this 
** file handle the initialization of ray directions, calculation of 
** distances, and the Digital Differential Analysis (DDA) algorithm 
** to determine wall intersections.
*/

static void	calculate_delta_distances(t_cub3d *mdata)
{
	if (mdata->render.ray_dir_x == 0)
		mdata->render.delta_dist_x = VERY_BIG;
	else
		mdata->render.delta_dist_x = fabs(1.0 / mdata->render.ray_dir_x);
	if (mdata->render.ray_dir_y == 0)
		mdata->render.delta_dist_y = VERY_BIG;
	else
		mdata->render.delta_dist_y = fabs(1.0 / mdata->render.ray_dir_y);
}

static double	calculate_side_distance(double player_pos, int map_pos, \
				double delta_dist, double ray_dir)
{
	if (ray_dir < 0)
		return ((player_pos - map_pos) * delta_dist);
	else
		return ((map_pos + 1.0 - player_pos) * delta_dist);
}

static void	initialize_ray_steps(t_cub3d *mdata)
{
	mdata->render.step_x = ft_tern_op(mdata->render.ray_dir_x < 0, -1, 1);
	mdata->render.step_y = ft_tern_op(mdata->render.ray_dir_y < 0, -1, 1);
	mdata->render.side_dist_x = calculate_side_distance(
			mdata->player_x / mdata->tile_size,
			mdata->render.map_x,
			mdata->render.delta_dist_x,
			mdata->render.ray_dir_x
			);
	mdata->render.side_dist_y = calculate_side_distance(
			mdata->player_y / mdata->tile_size,
			mdata->render.map_y,
			mdata->render.delta_dist_y,
			mdata->render.ray_dir_y
			);
}

static void	perform_dda(t_cub3d *mdata, int *hit)
{
	while (!(*hit))
	{
		if (mdata->render.side_dist_x < mdata->render.side_dist_y)
		{
			mdata->render.side_dist_x += mdata->render.delta_dist_x;
			mdata->render.map_x += mdata->render.step_x;
			mdata->render.side = 0;
		}
		else
		{
			mdata->render.side_dist_y += mdata->render.delta_dist_y;
			mdata->render.map_y += mdata->render.step_y;
			mdata->render.side = 1;
		}
		if (mdata->render.map_y < 0 \
			||mdata->render.map_y >= mdata->map_height \
			||mdata->render.map_x < 0 \
			||mdata->render.map_x >= mdata->map_width)
			*hit = 1;
		else if (mdata-> \
				map[mdata->render.map_y][mdata->render.map_x] == '1')
			*hit = 1;
	}
}

void	cub_cast_single_ray(t_cub3d *mdata)
{
	int	hit;

	mdata->render.ray_dir_x = cos(mdata->render.ray_angle);
	mdata->render.ray_dir_y = -sin(mdata->render.ray_angle);
	mdata->render.map_x = (int)(mdata->player_x / mdata->tile_size);
	mdata->render.map_y = (int)(mdata->player_y / mdata->tile_size);
	calculate_delta_distances(mdata);
	initialize_ray_steps(mdata);
	hit = 0;
	perform_dda(mdata, &hit);
	if (mdata->render.side == 0)
		mdata->render.perp_wall_dist = (mdata->render.map_x \
				-(mdata->player_x / mdata->tile_size) \
				+ (1 - mdata->render.step_x) / 2.0) \
				/mdata->render.ray_dir_x;
	else
		mdata->render.perp_wall_dist = (mdata->render.map_y \
				-(mdata->player_y / mdata->tile_size) \
				+ (1 - mdata->render.step_y) / 2.0) \
				/ mdata->render.ray_dir_y;
	if (mdata->render.perp_wall_dist < 0.0001)
		mdata->render.perp_wall_dist = 0.0001;
}
