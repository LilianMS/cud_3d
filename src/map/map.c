#include "cub3d.h"

static void	set_player_start(t_cub3d *mapdata, int row, int col, char start)
{
	mapdata->player_x = (col + 0.5f) * mapdata->tile_size;
	mapdata->player_y = (row + 0.5f) * mapdata->tile_size;
	if (start == 'N')
		mapdata->player_angle = M_PI / 2; // 90° = norte
	else if (start == 'S')
		mapdata->player_angle = 3 * M_PI / 2; // 270° = sul
	else if (start == 'E')
		mapdata->player_angle = 0; // 0° = leste
	else if (start == 'W')
		mapdata->player_angle = M_PI; // 180° = oeste
}

void	cub_player_start(t_cub3d *mapdata)
{
	char	start;
	int		row;
	int		col;

	row = 0;
	while (row < mapdata->map_height)
	{
		col = 0;
		while (col < mapdata->map_width)
		{
			start = mapdata->map[row][col];
			if (start == 'N' || start == 'S' || start == 'E' || start == 'W')
			{
				set_player_start(mapdata, row, col, start);
				return ;
			}
			col++;
		}
		row++;
	}
}

static void	draw_helper(t_cub3d *mapdata, int x_start, int y_start)
{
	int	y;
	int	x;
	int	x_end;
	int	y_end;

	x_end = x_start + mapdata->tile_size;
	y_end = y_start + mapdata->tile_size;
	y = y_start;
	while (y < y_end)
	{
		x = x_start;
		while (x < x_end)
		{
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				mlx_put_pixel(mapdata->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

static void	draw_tile(t_cub3d *mapdata, int row, int column)
{
	int	y_start;
	int	x_start;

	y_start = MINIMAP_OFFSET_Y + row * mapdata->tile_size;
	x_start = MINIMAP_OFFSET_X + column * mapdata->tile_size;
	draw_helper(mapdata, x_start, y_start);
}

void	draw_minimap(t_cub3d *mapdata)
{
	int	row;
	int	column;

	row = 0;
	while (row < mapdata->map_height)
	{
		column = 0;
		while (column < mapdata->map_width)
		{
			if (mapdata->map[row][column] == '1')
				draw_tile(mapdata, row, column);
			column++;
		}
		row++;
	}
}
