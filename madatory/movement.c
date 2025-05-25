#include "cub3d.h"

static void	movement_vector(t_cub3d *mdata, \
							float move_speed, float *dx, float *dy)
{
	*dx = 0.0f;
	*dy = 0.0f;
	if (mdata->keys[MLX_KEY_W])
	{
		*dx += move_speed * cos(mdata->player_angle);
		*dy -= move_speed * sin(mdata->player_angle);
	}
	if (mdata->keys[MLX_KEY_S])
	{
		*dx -= move_speed * cos(mdata->player_angle);
		*dy += move_speed * sin(mdata->player_angle);
	}
	if (mdata->keys[MLX_KEY_A])
	{
		*dx += move_speed * cos(mdata->player_angle + M_PI_2);
		*dy -= move_speed * sin(mdata->player_angle + M_PI_2);
	}
	if (mdata->keys[MLX_KEY_D])
	{
		*dx += move_speed * cos(mdata->player_angle - M_PI_2);
		*dy -= move_speed * sin(mdata->player_angle - M_PI_2);
	}
}

static void	player_rotation(t_cub3d *mdata, float rotate_speed)
{
	if (mdata->keys[MLX_KEY_LEFT])
		mdata->player_angle += rotate_speed;
	if (mdata->keys[MLX_KEY_RIGHT])
		mdata->player_angle -= rotate_speed;
	if (mdata->player_angle < 0)
		mdata->player_angle += 2 * M_PI;
	if (mdata->player_angle > 2 * M_PI)
		mdata->player_angle -= 2 * M_PI;
}

void	handle_movement(t_cub3d *mdata)
{
	float	dx;
	float	dy;
	float	move_speed;
	float	rotate_speed;

	move_speed = 0.5f;
	rotate_speed = 0.04f;
	movement_vector(mdata, move_speed, &dx, &dy);
	player_rotation(mdata, rotate_speed);
	wall_sliding(mdata, dx, dy);
}

void	deal_key(struct mlx_key_data keydata, void *param)
{
	t_cub3d	*mdata;

	mdata = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mdata->mlx);
	if (keydata.action == MLX_PRESS)
		mdata->keys[keydata.key] = true;
	else if (keydata.action == MLX_RELEASE)
		mdata->keys[keydata.key] = false;
}
