/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:51:20 by lilmende          #+#    #+#             */
/*   Updated: 2025/06/24 08:15:25 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_duplicate(t_cub3d *mdata, int *tab)
{
	char	**area;
	int		i;

	area = mdata->mapping.area;
	i = 0;
	while (area[i])
	{
		if (ft_strncmp(area[i], "NO", 2) == 0 && !ft_hash_table("N", tab))
			return (0);
		else if (ft_strncmp(area[i], "SO", 2) == 0 && !ft_hash_table("S", tab))
			return (0);
		else if (ft_strncmp(area[i], "WE", 2) == 0 && !ft_hash_table("W", tab))
			return (0);
		else if (ft_strncmp(area[i], "EA", 2) == 0 && !ft_hash_table("E", tab))
			return (0);
		else if (ft_strncmp(area[i], "F", 1) == 0 && !ft_hash_table("F", tab))
			return (0);
		else if (ft_strncmp(area[i], "C", 1) == 0 && !ft_hash_table("C", tab))
			return (0);
		i++;
	}
	return (1);
}

int	cub_search_elements(t_cub3d *mdata, const char *elements)
{
	int	table[256];

	ft_init_table(table, 256);
	if (!check_duplicate(mdata, table) \
		|| !check_all_chars(mdata->mapping.area, elements) \
		|| !cub_textures(mdata, 0) \
		|| !cub_colors(mdata))
		cub_error("Invalid Map!", mdata);
	return (1);
}

int	check_map_position(t_cub3d *mdata, int end)
{
	char	**area;
	int		x;

	area = mdata->mapping.area;
	if (area[end] == NULL)
		return (1);
	while (area[end])
	{
		x = 0;
		while (area[end][x] && ft_isspace(area[end][x]))
			x++;
		if (area[end][x] && area[end][x] != '\n' \
			&& area[end][x] != '\0' && !ft_isspace(area[end][x]))
		{
			cub_error("Map is not at the end of the file", mdata);
			return (0);
		}
		end++;
	}
	return (1);
}

void	spaces_before_data(t_cub3d *mdata, int i, int *j)
{
	*j = 0;
	while (ft_isspace(mdata->mapping.area[i][*j]))
		(*j)++;
}
