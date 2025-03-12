#include "cub3d.h"
#include <stdint.h> //para uint32_t

static int	is_wall(t_cub3d *mapdata, float x, float y)
{
	int	col;
	int	row;

	// Calcula em qual colua e linha o jogador está
	col = (int)(x / mapdata->tile_size); // O cast para int "arredonda" para o número da coluna atual
	row = (int)(y / mapdata->tile_size);
	// Se estiver fora do mapa
	if (row < 0 || row >= mapdata->map_height ||
		col < 0 || col >= mapdata->map_width)
		return (1);
	// Se a célula do mapa for 1
	if (mapdata->map[row * mapdata->map_width + col] == 1)
		return (1);
	else
		return (0);
}

static void	handle_movement(t_cub3d *mapdata, struct mlx_key_data keydata, float move_speed)
{
	float	old_x;
	float	old_y;

	old_x = mapdata->player_x;
	old_y = mapdata->player_y;
	if (keydata.key == MLX_KEY_W)
	{
		mapdata->player_x += move_speed * cos(mapdata->player_angle);
		mapdata->player_y += move_speed * sin(mapdata->player_angle);
	}
	else if (keydata.key == MLX_KEY_S)
	{
		mapdata->player_x -= move_speed * cos(mapdata->player_angle);
		mapdata->player_y -= move_speed * sin(mapdata->player_angle);
	}
	else if (keydata.key == MLX_KEY_A)
	{
		mapdata->player_x += move_speed * cos(mapdata->player_angle - M_PI_2); // ângulo - 90 graus
		mapdata->player_y += move_speed * sin(mapdata->player_angle - M_PI_2);
	}
	else if (keydata.key == MLX_KEY_D)
	{
		mapdata->player_x += move_speed * cos(mapdata->player_angle + M_PI_2);
		mapdata->player_y += move_speed * sin(mapdata->player_angle + M_PI_2);
	}
	else if (keydata.key == MLX_KEY_LEFT)
		mapdata->player_angle -= 0.1f;
	else if (keydata.key == MLX_KEY_RIGHT)
		mapdata->player_angle += 0.1f;
	if (is_wall(mapdata, mapdata->player_x, mapdata->player_y))
	{
		mapdata->player_x = old_x;
		mapdata->player_y = old_y;
	}
}

void	deal_key(struct mlx_key_data keydata, void *param)
{
	t_cub3d	*mapdata;

	mapdata = (t_cub3d *)param;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mapdata->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		handle_movement(mapdata, keydata, 5.0f); // 5.0f é a velocidade do movimento
}
