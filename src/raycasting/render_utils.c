/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:49:56 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/25 16:49:57 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_clear_3d_render(t_cub3d *mdata)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(mdata->img, x, y, mdata->mapping.c_color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(mdata->img, x, y, mdata->mapping.f_color);
			x++;
		}
		y++;
	}
}

void	cub_capture_texture(t_cub3d *mdata)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (mdata->render.side == 1)
	{
		if (mdata->render.step_y < 0)
			texture = mdata->texture.north;
		else
			texture = mdata->texture.south;
	}
	else
	{
		if (mdata->render.step_x < 0)
			texture = mdata->texture.west;
		else
			texture = mdata->texture.east;
	}
	mdata->texture.curr = texture;
}

uint32_t	cub_get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	int			texture_pos;
	uint8_t		*pixel;
	uint32_t	color;

	if (x < 0 \
		|| x >= (int)texture->width \
		|| y < 0 \
		|| y >= (int)texture->height)
		return (0);
	texture_pos = y * texture->width + x;
	texture_pos *= texture->bytes_per_pixel;
	pixel = &texture->pixels[texture_pos];
	color = (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
	return (color);
}
