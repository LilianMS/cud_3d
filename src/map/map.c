#include "cub3d.h"

/**
 * Directional angles used in the program:
 * - M_PI / 2 (90°): Represents the north direction.
 * - 3 * M_PI / 2 (270°): Represents the south direction.
 * - 0 (0°): Represents the east direction.
 * - M_PI (180°): Represents the west direction.
 *
 * These angles are expressed in radians and correspond to the standard
 * mathematical representation of directions on a unit circle.
 */

static void	set_player_start(t_cub3d *mdata, int row, int col, char start)
{
	mdata->player_x = (col + 0.5f) * mdata->tile_size;
	mdata->player_y = (row + 0.5f) * mdata->tile_size;
	if (start == 'N')
		mdata->player_angle = M_PI / 2;
	else if (start == 'S')
		mdata->player_angle = 3 * M_PI / 2;
	else if (start == 'E')
		mdata->player_angle = 0;
	else if (start == 'W')
		mdata->player_angle = M_PI;
}

void	cub_player_start(t_cub3d *mdata)
{
	char	start;
	int		row;
	int		col;

	row = 0;
	while (row < mdata->map_height)
	{
		col = 0;
		while (col < mdata->map_width)
		{
			start = mdata->map[row][col];
			if (start == 'N' || start == 'S' || start == 'E' || start == 'W')
			{
				set_player_start(mdata, row, col, start);
				return ;
			}
			col++;
		}
		row++;
	}
}

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
