#include "cub3d.h"
#include <stdint.h> //para uint32_t

void	deal_key(struct mlx_key_data keydata, void *param)
{
	t_cub3d	*mapdata;
	float	move_speed;
	float 	old_x;
	float 	old_y;

	move_speed = 5.0f; //ajustar velocidade do movimento
	mapdata = (t_cub3d *)param;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mapdata->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		old_x = mapdata->player_x;
		old_y = mapdata->player_y;
		if (keydata.key == MLX_KEY_W)
			mapdata->player_y -= move_speed; // “W” move pra cima (diminuindo Y)
		if (keydata.key == MLX_KEY_S)
			mapdata->player_y += move_speed; // “S” move pra baixo
		if (keydata.key == MLX_KEY_A)
			mapdata->player_x -= move_speed; // “A” move à esquerda
		if (keydata.key == MLX_KEY_D)
			mapdata->player_x += move_speed; // “D” move à direita
		if (is_wall(mapdata, mapdata->player_x, mapdata->player_y))
		{
			mapdata->player_x = old_x;
			mapdata->player_y = old_y;
		}
	}
}

// Retorna 1 (true) se for parede, 0 (false) caso contrário
int is_wall(t_cub3d *mapdata, float x, float y)
{
	int col;
	int row;

	// Calcula em qual colua e linha o jogador está
	col = (int)(x / mapdata->tile_size);
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

