#include "cub3d.h"

static void	draw_helper(t_cub3d *mdata, int x_start, int y_start)
{
	int	y;
	int	x;
	int	x_end;
	int	y_end;

	x_end = x_start + mdata->tile_size;
	y_end = y_start + mdata->tile_size;
	y = y_start;
	while (y < y_end)
	{
		x = x_start;
		while (x < x_end)
		{
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				mlx_put_pixel(mdata->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

static void	draw_tile(t_cub3d *mdata, int row, int column)
{
	int	y_start;
	int	x_start;

	y_start = MINIMAP_OFFSET_Y + row * mdata->tile_size;
	x_start = MINIMAP_OFFSET_X + column * mdata->tile_size;
	draw_helper(mdata, x_start, y_start);
}

void	draw_minimap(t_cub3d *mdata)
{
	int	row;
	int	column;

	row = 0;
	while (row < mdata->map_height)
	{
		column = 0;
		while (column < mdata->map_width)
		{
			if (mdata->map[row][column] == '1')
				draw_tile(mdata, row, column);
			column++;
		}
		row++;
	}
}
