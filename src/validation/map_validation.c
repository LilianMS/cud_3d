#include "cub3d.h"

void	cub_player_validation(t_cub3d *mapdata, t_pos pos)
{
	int	player_count;

	player_count = 0;
	while (mapdata->map[pos.y])
	{
		pos.x = 0;
		while (mapdata->map[pos.y][pos.x])
		{
			if (ft_strchr("NSEW", mapdata->map[pos.y][pos.x]))
			{
				player_count++;
				mapdata->player_dir = mapdata->map[pos.y][pos.x];
				mapdata->p_pos.x = pos.x;
				mapdata->p_pos.y = pos.y;
			}
			pos.x++;
		}
		pos.y++;
	}
	if (player_count != 1)
		cub_error("Multiple players in map or no player!", mapdata);
}

static void	if_pos_zero(t_cub3d *mapdata, t_pos pos)
{
	if ((pos.y + 1 >= mapdata->map_height || pos.x + 1 >= mapdata->map_width \
		|| pos.y - 1 < 0 || pos.x - 1 < 0) \
		|| (mapdata->map[pos.y + 1][pos.x] == '\0' \
			|| mapdata->map[pos.y + 1][pos.x] == ' ' \
			|| mapdata->map[pos.y + 1][pos.x] == '\n' \
			|| mapdata->map[pos.y + 1][pos.x] == '9') \
		|| (mapdata->map[pos.y][pos.x + 1] == '\0' \
			|| mapdata->map[pos.y][pos.x + 1] == ' ' \
			|| mapdata->map[pos.y][pos.x + 1] == '\n' \
			|| mapdata->map[pos.y][pos.x + 1] == '9') \
		|| (mapdata->map[pos.y - 1][pos.x] == '\0' \
			|| mapdata->map[pos.y - 1][pos.x] == ' ' \
			|| mapdata->map[pos.y - 1][pos.x] == '\n' \
			|| mapdata->map[pos.y - 1][pos.x] == '9') \
		|| (mapdata->map[pos.y][pos.x - 1] == '\0' \
			|| mapdata->map[pos.y][pos.x - 1] == ' ' \
			|| mapdata->map[pos.y][pos.x - 1] == '\n' \
			|| mapdata->map[pos.y][pos.x - 1] == '9'))
		cub_error("Invalid wall in map!", mapdata);
}

static void	is_valid_walls(t_cub3d *mapdata, t_pos pos)
{
	while (mapdata->map[pos.y])
	{
		pos.x = 0;
		while (mapdata->map[pos.y][pos.x])
		{
			if (mapdata->map[pos.y][pos.x] == '0')
				if_pos_zero(mapdata, (t_pos){pos.x, pos.y});
			else if (ft_strchr("NSEW", mapdata->map[pos.y][pos.x]))
			{
				if_pos_zero(mapdata, (t_pos){pos.x, pos.y});
				if (ft_if_surrounded_by_walls(mapdata->map, \
												(t_pos){pos.x, pos.y}, '1'))
					cub_error("The player is walled in!!!", mapdata);
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	cub_check_area_visited(t_cub3d *mapdata)
{
	int	i;
	int	j;

	i = 0;
	while (mapdata->flood_map[i])
	{
		j = 0;
		while (mapdata->flood_map[i][j])
		{
			if (mapdata->flood_map[i][j] == '0')
				cub_error("Invalid path!", mapdata);
			j++;
		}
		i++;
	}
}

void	cub_map_validation(t_cub3d *mapdata, t_pos p_pos)
{
	(void) p_pos;
	is_valid_walls(mapdata, (t_pos){0, 0}); // checa se o mapa está fechado
	copy_map(mapdata);
	cub_flood_fill(mapdata, p_pos);
//////////////////////////////////
	print_area(mapdata->flood_map); // debug
/////////////////////////////////
	cub_check_area_visited(mapdata); // checar se o caminho é válido
}
