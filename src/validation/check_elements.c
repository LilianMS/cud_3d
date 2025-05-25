/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:44 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/25 16:50:45 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_color_values(char **colors)
{
	const char	*str;
	int			i;
	int			value;

	i = 0;
	while (i < 3)
	{
		str = colors[i];
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (0);
			str++;
		}
		value = ft_atoi(colors[i]);
		if (value && (value < 0 || value > 255))
			return (0);
		i++;
	}
	return (1);
}

static int	*ft_convert_to_int_array(char **array, int n)
{
	int	*int_array;
	int	i;

	int_array = malloc(sizeof(int) * n);
	if (!int_array)
		return (NULL);
	i = 0;
	while (i < n)
	{
		int_array[i] = ft_atoi(array[i]);
		i++;
	}
	ft_free_split(array);
	array = NULL;
	free(array);
	return (int_array);
}

static int	*cub_handle_colors(t_cub3d *mdata, int i, int j)
{
	char	**colors;

	if (ft_isspace(mdata->mapping.area[i][j]))
		while (ft_isspace(mdata->mapping.area[i][j]))
			j++;
	colors = ft_split(mdata->mapping.area[i] + j, ',');
	ft_remove_newline(&colors);
	ft_remove_end_spaces(&colors[2]);
	if (colors)
	{
		if (ft_array_len(colors) != 3 || !validate_color_values(colors))
		{
			ft_free_split(colors);
			return (NULL);
		}
		return (ft_convert_to_int_array(colors, 3));
	}
	return (NULL);
}

static int	check_color_data(t_cub3d *mdata)
{
	int	*c;
	int	i;

	i = 0;
	while (mdata->mapping.area[i])
	{
		if (mdata->mapping.area[i][0] == 'F' \
			|| mdata->mapping.area[i][0] == 'C')
		{
			c = cub_handle_colors(mdata, i, 1);
			if (c)
			{
				if (mdata->mapping.area[i][0] == 'F')
					mdata->mapping.f_color = ft_rgb_to_int(c[0], c[1], c[2]);
				else
					mdata->mapping.c_color = ft_rgb_to_int(c[0], c[1], c[2]);
				free(c);
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	cub_colors(t_cub3d *mdata)
{
	if (!check_color_data(mdata) \
		|| !mdata->mapping.f_color \
		|| !mdata->mapping.c_color)
	{
		cub_error("Invalid color data!", mdata);
		return (0);
	}
	return (1);
}
