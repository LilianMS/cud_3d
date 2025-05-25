/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:31 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/25 16:50:32 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_remove_newline(char ***colors)
{
	char	*newline;
	int		i;

	i = 0;
	while ((*colors)[i])
	{
		newline = ft_strchr((*colors)[i], '\n');
		if (newline)
			*newline = '\0';
		i++;
	}
}

int	ft_array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

int	ft_if_surrounded_by_walls(char **area, t_pos pos, char wall)
{
	if (area[pos.y + 1][pos.x] == wall \
		&& area[pos.y][pos.x + 1] == wall \
		&& area[pos.y - 1][pos.x] == wall \
		&& area[pos.y][pos.x - 1] == wall)
		return (1);
	return (0);
}

int	ft_check_kind_file(char *str, char *suffix)
{
	int		len;
	int		i;

	if (!str || !suffix)
		return (0);
	ft_remove_end_spaces(&str);
	i = ft_strlen(suffix) - 1;
	len = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[len--] != suffix[i--])
			return (0);
	}
	return (1);
}

uint32_t	ft_rgb_to_int(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}
