#include "cub3d.h"

void	init_map (t_cub3d *mapdata) //função mapa placeholder
{
	static int local_map[64] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1
	};
	mapdata->map_width = 8;
	mapdata->map_height = 8;
	mapdata->tile_size = 64;
	mapdata->map = local_map;
} // fim do mapa placeholder


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
			mlx_put_pixel(mapdata->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

static void	draw_tile (t_cub3d *mapdata, int row, int column)
{
	int	y_start;
	int	x_start;

	y_start = row * mapdata->tile_size;
	x_start = column * mapdata->tile_size;
	draw_helper(mapdata, x_start, y_start);
}

void	draw_minimap (t_cub3d *mapdata)
{
	int	row;
	int	column;

	row = 0;
	while (row < mapdata->map_height)
	{
		column = 0;
		while (column < mapdata->map_width)
		{
			if (mapdata->map[row * mapdata->map_width + column] == 1)
				draw_tile(mapdata, row, column);
			column++;
		}
		row++;
	}
}
