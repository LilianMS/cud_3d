#include "cub3d.h"

void	cub_clear_3d_render(t_cub3d *mapdata)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(mapdata->img, x, y, mapdata->mapping.c_color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(mapdata->img, x, y, mapdata->mapping.f_color);
			x++;
		}
		y++;
	}
}

void	cub_capture_texture(t_cub3d *game)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (game->render.side == 1)
	{
		if (game->render.step_y < 0)
			texture = game->texture.north;
		else
			texture = game->texture.south;
	}
	else
	{
		if (game->render.step_x < 0)
			texture = game->texture.west;
		else
			texture = game->texture.east;
	}
	game->texture.curr = texture;
}

uint32_t	cub_get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	int		texture_pos;
	uint8_t	*pixel;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	texture_pos = y * texture->width + x;
	texture_pos *= texture->bytes_per_pixel;
	pixel = &texture->pixels[texture_pos];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}
