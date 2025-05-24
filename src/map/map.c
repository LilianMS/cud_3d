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
