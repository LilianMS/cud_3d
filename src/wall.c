#include "cub3d.h"

int	is_wall(t_cub3d *mapdata, float x, float y)
{
	int	col;
	int	row;

	// Calcula em qual colua e linha o jogador está
	col = (int)(x / mapdata->tile_size); // O cast para int "arredonda" para o número da coluna atual
	row = (int)(y / mapdata->tile_size);
	// Se estiver fora do mapa
	if (row < 0 || row >= mapdata->map_height
		|| col < 0 || col >= mapdata->map_width)
		return (1);
	// Se a célula do mapa for 1
	if (mapdata->map[row * mapdata->map_width + col] == 1)
		return (1);
	else
		return (0);
}

void	wall_sliding(t_cub3d *mapdata, float dx, float dy)
{
	float	old_x;
	float	old_y;

	old_x = mapdata->player_x;
	old_y = mapdata->player_y;
	mapdata->player_x += dx;
	if (is_wall(mapdata, mapdata->player_x, mapdata->player_y))
		mapdata->player_x = old_x;
	mapdata->player_y += dy;
	if (is_wall(mapdata, mapdata->player_x, mapdata->player_y))
		mapdata->player_y = old_y;
}
