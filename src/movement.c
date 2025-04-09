#include "cub3d.h"

static void movement_vector(t_cub3d *mapdata, float move_speed, float *dx, float *dy)
{
    *dx = 0.0f;
    *dy = 0.0f;

    // Para andar “para frente” (W), somamos cos no X e subtraímos sin no Y.
    if (mapdata->keys[MLX_KEY_W])
    {
        *dx += move_speed * cos(mapdata->player_angle);
        *dy -= move_speed * sin(mapdata->player_angle);
    }
    // Para andar “para trás” (S), é o oposto.
    if (mapdata->keys[MLX_KEY_S])
    {
        *dx -= move_speed * cos(mapdata->player_angle);
        *dy += move_speed * sin(mapdata->player_angle);
    }
    // Para strafe esquerdo (A): ângulo = player_angle - π/2
	if (mapdata->keys[MLX_KEY_A])
	{
		*dx += move_speed * cos(mapdata->player_angle + M_PI_2);
		*dy -= move_speed * sin(mapdata->player_angle + M_PI_2);
	}
    // Para strafe direito (D): ângulo = player_angle + π/2
	if (mapdata->keys[MLX_KEY_D])
	{
		*dx += move_speed * cos(mapdata->player_angle - M_PI_2);
		*dy -= move_speed * sin(mapdata->player_angle - M_PI_2);
	}
}

static void	player_rotation(t_cub3d *mapdata, float rotate_speed)
{
	if (mapdata->keys[MLX_KEY_LEFT])
		mapdata->player_angle += rotate_speed;
	if (mapdata->keys[MLX_KEY_RIGHT])
		mapdata->player_angle -= rotate_speed;
	if (mapdata->player_angle < 0)
		mapdata->player_angle += 2 * M_PI;
	if (mapdata->player_angle > 2 * M_PI)
		mapdata->player_angle -= 2 * M_PI;
}

void	handle_movement(t_cub3d *mapdata)
{
	float	dx;
	float	dy;
	float	move_speed;
	float	rotate_speed;

	move_speed = 5.0f;
	rotate_speed = 0.1f;
	movement_vector(mapdata, move_speed, &dx, &dy);
	player_rotation(mapdata, rotate_speed);
	wall_sliding(mapdata, dx, dy);
}

void	deal_key(struct mlx_key_data keydata, void *param)
{
	t_cub3d	*mapdata;

	mapdata = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mapdata->mlx);
	if (keydata.action == MLX_PRESS)
		mapdata->keys[keydata.key] = true;
	else if (keydata.action == MLX_RELEASE)
		mapdata->keys[keydata.key] = false;
}
