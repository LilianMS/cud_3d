#include "cub3d.h"

int	is_wall(t_cub3d *mdata, float x, float y)
{
	int	col;
	int	row;

	col = (int)(x / mdata->tile_size);
	row = (int)(y / mdata->tile_size);
	if (row < 0 || row >= mdata->map_height
		|| col < 0 || col >= mdata->map_width)
		return (1);
	if (mdata->map[row][col] == '1')
		return (1);
	else
		return (0);
}

void	wall_sliding(t_cub3d *mdata, float dx, float dy)
{
	float	old_x;
	float	old_y;

	old_x = mdata->player_x;
	old_y = mdata->player_y;
	mdata->player_x += dx;
	if (is_wall(mdata, mdata->player_x, mdata->player_y))
		mdata->player_x = old_x;
	mdata->player_y += dy;
	if (is_wall(mdata, mdata->player_x, mdata->player_y))
		mdata->player_y = old_y;
}
