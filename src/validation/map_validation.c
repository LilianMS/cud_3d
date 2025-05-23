#include "cub3d.h"

void	cub_player_validation(t_cub3d *mdata, t_pos pos)
{
	int	player_count;

	player_count = 0;
	while (mdata->map[pos.y])
	{
		pos.x = 0;
		while (mdata->map[pos.y][pos.x])
		{
			if (ft_strchr("NSEW", mdata->map[pos.y][pos.x]))
			{
				player_count++;
				mdata->player_dir = mdata->map[pos.y][pos.x];
				mdata->p_pos.x = pos.x;
				mdata->p_pos.y = pos.y;
			}
			pos.x++;
		}
		pos.y++;
	}
	if (player_count != 1)
		cub_error("Multiple players in map or no player!", mdata);
}

static void	if_pos_zero(t_cub3d *mdata, t_pos pos)
{
	if ((pos.y + 1 >= mdata->map_height || pos.x + 1 >= mdata->map_width \
		|| pos.y - 1 < 0 || pos.x - 1 < 0) \
		|| (mdata->map[pos.y + 1][pos.x] == '\0' \
			|| mdata->map[pos.y + 1][pos.x] == ' ' \
			|| mdata->map[pos.y + 1][pos.x] == '\n' \
			|| mdata->map[pos.y + 1][pos.x] == '9') \
		|| (mdata->map[pos.y][pos.x + 1] == '\0' \
			|| mdata->map[pos.y][pos.x + 1] == ' ' \
			|| mdata->map[pos.y][pos.x + 1] == '\n' \
			|| mdata->map[pos.y][pos.x + 1] == '9') \
		|| (mdata->map[pos.y - 1][pos.x] == '\0' \
			|| mdata->map[pos.y - 1][pos.x] == ' ' \
			|| mdata->map[pos.y - 1][pos.x] == '\n' \
			|| mdata->map[pos.y - 1][pos.x] == '9') \
		|| (mdata->map[pos.y][pos.x - 1] == '\0' \
			|| mdata->map[pos.y][pos.x - 1] == ' ' \
			|| mdata->map[pos.y][pos.x - 1] == '\n' \
			|| mdata->map[pos.y][pos.x - 1] == '9'))
		cub_error("Invalid wall in map!", mdata);
}

static void	is_valid_walls(t_cub3d *mdata, t_pos pos)
{
	while (mdata->map[pos.y])
	{
		pos.x = 0;
		while (mdata->map[pos.y][pos.x])
		{
			if (mdata->map[pos.y][pos.x] == '0')
				if_pos_zero(mdata, (t_pos){pos.x, pos.y});
			else if (ft_strchr("NSEW", mdata->map[pos.y][pos.x]))
			{
				if_pos_zero(mdata, (t_pos){pos.x, pos.y});
				if (ft_if_surrounded_by_walls(mdata->map, \
												(t_pos){pos.x, pos.y}, '1'))
					cub_error("The player is walled in!!!", mdata);
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	cub_check_area_visited(t_cub3d *mdata)
{
	int	i;
	int	j;

	i = 0;
	while (mdata->flood_map[i])
	{
		j = 0;
		while (mdata->flood_map[i][j])
		{
			if (mdata->flood_map[i][j] == '0')
				cub_error("Invalid path!", mdata);
			j++;
		}
		i++;
	}
}

void	cub_map_validation(t_cub3d *mdata, t_pos p_pos)
{
	(void) p_pos;
	is_valid_walls(mdata, (t_pos){0, 0}); // checa se o mapa está fechado
	copy_map(mdata);
	cub_flood_fill(mdata, p_pos);
//////////////////////////////////
	print_area(mdata->flood_map); // debug
/////////////////////////////////
	cub_check_area_visited(mdata); // checar se o caminho é válido
}
