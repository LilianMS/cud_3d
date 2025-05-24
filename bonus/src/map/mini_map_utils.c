#include "cub3d.h"

void	clear_minimap_area(t_cub3d *mdata)
{
	int	x;
	int	y;
	int	color;
	int	width;
	int	height;

	color = 0x333333FF;
	width = MINIMAP_OFFSET_X + (mdata->map_width * mdata->tile_size);
	height = MINIMAP_OFFSET_Y + (mdata->map_height * mdata->tile_size);
	y = MINIMAP_OFFSET_Y;
	while (y < height)
	{
		x = MINIMAP_OFFSET_X;
		while (x < width)
		{
			mlx_put_pixel(mdata->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_player(t_cub3d *mdata)
{
	int	dx;
	int	dy;
	int	px;
	int	py;
	int	player_size;

	player_size = mdata->tile_size / 8;
	dy = -player_size;
	while (dy <= player_size)
	{
		dx = -player_size;
		while (dx <= player_size)
		{
			px = MINIMAP_OFFSET_X + (int)(mdata->player_x + dx);
			py = MINIMAP_OFFSET_Y + (int)(mdata->player_y + dy);
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
				mlx_put_pixel(mdata->img, px, py, 0xFFFF00FF);
			dx++;
		}
		dy++;
	}
}

void	render_direction(t_cub3d *mdata)
{
	float	dir_x;
	float	dir_y;
	int		i;
	int		px;
	int		py;

	dir_x = cos(mdata->player_angle);
	dir_y = sin(mdata->player_angle);
	i = 0;
	while (i < 20)
	{
		px = MINIMAP_OFFSET_X + (int)(mdata->player_x + dir_x * i);
		py = MINIMAP_OFFSET_Y + (int)(mdata->player_y - dir_y * i);
		if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
			mlx_put_pixel(mdata->img, px, py, 0xFFA500FF);
		i++;
	}
}
