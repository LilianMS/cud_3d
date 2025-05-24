#include "cub3d.h"

static void	draw_helper(mlx_image_t *target, int x_start, int y_start, int size)
{
	int	x;
	int	y;
	int	x_end;
	int	y_end;

	x_end = x_start + size;
	y_end = y_start + size;
	y = y_start;
	while (y < y_end)
	{
		x = x_start;
		while (x < x_end)
		{
			mlx_put_pixel(target, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

static void	draw_tile(t_cub3d *mdata, mlx_image_t *target, int row, int col)
{
	int	x_start;
	int	y_start;

	x_start = MINIMAP_OFFSET_X + col * mdata->tile_size;
	y_start = MINIMAP_OFFSET_Y + row * mdata->tile_size;
	draw_helper(target, x_start, y_start, mdata->tile_size);
}

void	draw_minimap_static(t_cub3d *mdata)
{
	int	row;
	int	col;

	row = 0;
	while (row < mdata->map_height)
	{
		col = 0;
		while (col < mdata->map_width)
		{
			if (mdata->map[row][col] == '1')
				draw_tile(mdata, mdata->minimap_static, row, col);
			col++;
		}
		row++;
	}
}

void	render_player_on_minimap(t_cub3d *mdata)
{
	int	dx;
	int	dy;
	int	px;
	int	py;
	int	size;

	size = mdata->tile_size / 8;
	dy = -size;
	while (dy <= size)
	{
		dx = -size;
		while (dx <= size)
		{
			px = MINIMAP_OFFSET_X + (int)(mdata->player_x + dx);
			py = MINIMAP_OFFSET_Y + (int)(mdata->player_y + dy);
			if (px >= 0 && (uint32_t)px < mdata->minimap_dynamic->width
				&& py >= 0 && (uint32_t)py < mdata->minimap_dynamic->height)
				mlx_put_pixel(mdata->minimap_dynamic, px, py, 0xFFFF00FF);
			dx++;
		}
		dy++;
	}
}

void	render_direction_on_minimap(t_cub3d *mdata)
{
	int		i;
	int		px;
	int		py;
	float	dir_x;
	float	dir_y;

	dir_x = cos(mdata->player_angle);
	dir_y = sin(mdata->player_angle);
	i = 0;
	while (i < 20)
	{
		px = MINIMAP_OFFSET_X + (int)(mdata->player_x + dir_x * i);
		py = MINIMAP_OFFSET_Y + (int)(mdata->player_y - dir_y * i);
		if (px >= 0 && (uint32_t)px < mdata->minimap_dynamic->width
			&& py >= 0 && (uint32_t)py < mdata->minimap_dynamic->height)
			mlx_put_pixel(mdata->minimap_dynamic, px, py, 0xFFA500FF);
		i++;
	}
}
