/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:39 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/25 16:50:40 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	per_line(char *str, char c)
{
	int	j;
	int	found;

	found = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == c)
		{
			found = 1;
			break ;
		}
		j++;
	}
	return (found);
}

int	check_all_chars(char **area, const char *valid_chars)
{
	const char	*ch = valid_chars;
	int			found;
	int			i;

	found = 0;
	while (*ch)
	{
		i = 0;
		while (area[i])
		{
			found = per_line(area[i], *ch);
			if (found)
				break ;
			i++;
		}
		if (!found)
			return (0);
		ch++;
	}
	return (1);
}
