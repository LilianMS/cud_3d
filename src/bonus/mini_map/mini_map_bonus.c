/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:03:54 by lilmende          #+#    #+#             */
/*   Updated: 2025/06/24 07:32:42 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"

void	clear_minimap_dynamic(t_cub3d *mdata)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < mdata->minimap_dynamic->height)
	{
		x = 0;
		while (x < mdata->minimap_dynamic->width)
		{
			mlx_put_pixel(mdata->minimap_dynamic, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	update_minimap_dynamic(t_cub3d *mdata)
{
	clear_minimap_dynamic(mdata);
	render_player_on_minimap(mdata);
	render_direction_on_minimap(mdata);
}

void	init_minimap(t_cub3d *mdata)
{
	mdata->minimap_static = mlx_new_image(mdata->mlx,
			MINIMAP_AREA_W, MINIMAP_AREA_H);
	mdata->minimap_dynamic = mlx_new_image(mdata->mlx,
			MINIMAP_AREA_W, MINIMAP_AREA_H);
	if (!mdata->minimap_static || !mdata->minimap_dynamic)
		cub_error("Failed to create minimap images", mdata);
	mlx_image_to_window(mdata->mlx, mdata->minimap_static, 10, 10);
	mlx_image_to_window(mdata->mlx, mdata->minimap_dynamic, 10, 10);
	mdata->minimap_static->enabled = false;
	mdata->minimap_dynamic->enabled = false;
	draw_minimap_static(mdata);
}
