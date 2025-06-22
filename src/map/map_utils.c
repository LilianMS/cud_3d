/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:49:24 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/25 16:49:25 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calculate_tile_size(int map_width, int map_height)
{
	int	tile_w;
	int	tile_h;

	tile_w = MINIMAP_AREA_W / map_width;
	tile_h = MINIMAP_AREA_H / map_height;
	if (tile_w < tile_h)
		return (tile_w);
	else
		return (tile_h);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || line[0] == '\n')
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			i++;
			continue ;
		}
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	find_map_start(char **area)
{
	int	start;

	start = 0;
	while (area[start] && !is_map_line(area[start]))
		start++;
	if (area[start])
		return (start);
	else
		return (-1);
}

static int	find_map_end(char **area, int start)
{
	int	end;

	end = start;
	while (area[end] && is_map_line(area[end]))
		end++;
	return (end);
}

void	cub_extract_map(t_cub3d *mdata)
{
	int	start;
	int	end;
	int	map_lines;

	start = find_map_start(mdata->mapping.area);
	if (start == -1)
		cub_error("Map not found in file!", mdata);
	end = find_map_end(mdata->mapping.area, start);
	map_lines = end - start;
	check_map_position(mdata, end);
	allocate_copy_map(mdata, start, map_lines, (t_pos){0, 0});
}
