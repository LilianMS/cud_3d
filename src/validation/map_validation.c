#include "cub3d.h"

void	cub_player_validation(t_cub3d *mapdata, t_pos pos)
{
	int player_count;

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
		cub_error("Multiple players in map!", mapdata);
}







void	map_validation(t_cub3d *mapdata)
{
	int i;
	int j;

	i = 0;
	while (mapdata->mapping.area[i])
	{
		j = 0;
		while (mapdata->mapping.area[i][j])
		{
			if (!ft_strchr("01NSEW ", mapdata->mapping.area[i][j]))
				cub_error("Invalid character in map!", mapdata);
			j++;
		}
		i++;
	}
}