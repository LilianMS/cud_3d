#include "cub3d.h"

static void	calculate_delta_distances(t_cub3d *mapdata)
{
	if (mapdata->render.ray_dir_x == 0)
		mapdata->render.delta_dist_x = VERY_BIG;
	else
		mapdata->render.delta_dist_x = fabs(1.0 / mapdata->render.ray_dir_x);
	if (mapdata->render.ray_dir_y == 0)
		mapdata->render.delta_dist_y = VERY_BIG;
	else
		mapdata->render.delta_dist_y = fabs(1.0 / mapdata->render.ray_dir_y);
}

static double	calculate_side_distance(double player_pos, int map_pos, \
				double delta_dist, double ray_dir)
{
	if (ray_dir < 0)
		return ((player_pos - map_pos) * delta_dist);
	else
		return ((map_pos + 1.0 - player_pos) * delta_dist);
}

static void	initialize_ray_steps(t_cub3d *mapdata)
{
	mapdata->render.step_x = ft_tern_op(mapdata->render.ray_dir_x < 0, -1, 1);
	mapdata->render.step_y = ft_tern_op(mapdata->render.ray_dir_y < 0, -1, 1);
	mapdata->render.side_dist_x = calculate_side_distance(
			mapdata->player_x / mapdata->tile_size,
			mapdata->render.map_x,
			mapdata->render.delta_dist_x,
			mapdata->render.ray_dir_x
			);
	mapdata->render.side_dist_y = calculate_side_distance(
			mapdata->player_y / mapdata->tile_size,
			mapdata->render.map_y,
			mapdata->render.delta_dist_y,
			mapdata->render.ray_dir_y
			);
}

static void	perform_dda(t_cub3d *mapdata, int *hit)
{
	while (!(*hit))
	{
		if (mapdata->render.side_dist_x < mapdata->render.side_dist_y)
		{
			mapdata->render.side_dist_x += mapdata->render.delta_dist_x;
			mapdata->render.map_x += mapdata->render.step_x;
			mapdata->render.side = 0;
		}
		else
		{
			mapdata->render.side_dist_y += mapdata->render.delta_dist_y;
			mapdata->render.map_y += mapdata->render.step_y;
			mapdata->render.side = 1;
		}
		if (mapdata->render.map_y < 0 \
			|| mapdata->render.map_y >= mapdata->map_height \
			|| mapdata->render.map_x < 0 \
			|| mapdata->render.map_x >= mapdata->map_width)
			*hit = 1;
		else if (mapdata-> \
				map[mapdata->render.map_y][mapdata->render.map_x] == '1')
			*hit = 1;
	}
}

void	cub_cast_single_ray(t_cub3d *mapdata)
{
	int	hit;

	mapdata->render.ray_dir_x = cos(mapdata->render.ray_angle);
	mapdata->render.ray_dir_y = -sin(mapdata->render.ray_angle);
	mapdata->render.map_x = (int)(mapdata->player_x / mapdata->tile_size);
	mapdata->render.map_y = (int)(mapdata->player_y / mapdata->tile_size);
	calculate_delta_distances(mapdata);
	initialize_ray_steps(mapdata);
	hit = 0;
	perform_dda(mapdata, &hit);
	if (mapdata->render.side == 0)
		mapdata->render.perp_wall_dist = (mapdata->render.map_x \
				- (mapdata->player_x / mapdata->tile_size) \
				+ (1 - mapdata->render.step_x) / 2.0) \
				/ mapdata->render.ray_dir_x;
	else
		mapdata->render.perp_wall_dist = (mapdata->render.map_y \
				- (mapdata->player_y / mapdata->tile_size) \
				+ (1 - mapdata->render.step_y) / 2.0) \
				/ mapdata->render.ray_dir_y;
	if (mapdata->render.perp_wall_dist < 0.0001)
		mapdata->render.perp_wall_dist = 0.0001;
}
