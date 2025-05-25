/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:48:33 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/25 17:07:17 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation_bonus.h"
#include "cub3d.h"

void	set_hud_position(mlx_image_t *img, int offset_x, int offset_y)
{
	img->instances[0].x = (WIDTH / 2) - (img->width / 2) + offset_x;
	img->instances[0].y = HEIGHT - img->height + offset_y;
}

void	clear_image(mlx_image_t *img)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, 0);
			x++;
		}
		y++;
	}
}
