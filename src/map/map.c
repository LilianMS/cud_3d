/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:49:37 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/26 22:50:34 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
