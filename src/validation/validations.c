/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:51:27 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/25 17:30:36 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_read_file(t_cub3d *mdata)
{
	int		fd;
	int		i;

	fd = open(mdata->mapping.file, O_RDONLY);
	if (fd == -1)
		cub_error("Error open file!", mdata);
	i = 0;
	mdata->mapping.area = malloc(sizeof(char *) * MAX_LINES);
	if (!mdata->mapping.area)
		cub_error("Memory allocation failed!", mdata);
	mdata->mapping.area[i] = get_next_line(fd);
	if (!mdata->mapping.area[i])
		cub_error("Invalid Map!", mdata);
	mdata->mapping.lines = 0;
	while (mdata->mapping.area[i])
	{
		mdata->mapping.lines++;
		i++;
		mdata->mapping.area[i] = get_next_line(fd);
	}
	mdata->mapping.area[i + 1] = NULL;
	close(fd);
	return (1);
}

static void	cub_read_area(t_cub3d *mdata)
{
	cub_extract_map(mdata);
	cub_player_validation(mdata, (t_pos){0, 0});
	mdata->tile_size = calculate_tile_size(mdata->map_width, \
												mdata->map_height);
	cub_map_validation(mdata, mdata->p_pos);
	cub_player_start(mdata);
}

int	cub_check_invalid_chars(t_cub3d *mdata, t_pos pos)
{
	char	**a;

	a = mdata->mapping.area;
	while (a[pos.y])
	{
		pos.x = 0;
		if (ft_strchr("EWNSFC", a[pos.y][pos.x]))
			pos.y++;
		while (a[pos.y] && ft_isspace(a[pos.y][pos.x]))
			pos.x++;
		if (a[pos.y] && ft_strchr("01", a[pos.y][pos.x]))
		{
			while (a[pos.y][pos.x] && ft_strchr("01NSEW ", a[pos.y][pos.x]))
				pos.x++;
			if (a[pos.y][pos.x] == '\0' || a[pos.y][pos.x] == '\n')
				pos.y++;
			else
				cub_error("Invalid character in map!", mdata);
		}
		else if (a[pos.y] && !ft_strchr("EWNSFC", a[pos.y][pos.x]))
			cub_error("Invalid character in map!", mdata);
		else
			pos.y++;
	}
	return (1);
}

int	cub_valid(t_cub3d *mdata)
{
	if (!mdata->mapping.file)
		cub_error("Argument with 'file.cub' is required!", mdata);
	if (!ft_check_kind_file(mdata->mapping.file, ".cub"))
		cub_error("Incorrect file type. It's not '*.cub'!", mdata);
	cub_read_file(mdata);
	cub_search_elements(mdata, "NSWEAOFC");
	cub_check_invalid_chars(mdata, (t_pos){0, 0});
	cub_read_area(mdata);
	return (1);
}
