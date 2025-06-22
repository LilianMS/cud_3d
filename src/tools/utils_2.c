/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:22 by lilmende          #+#    #+#             */
/*   Updated: 2025/06/22 18:49:36 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_remove_end_spaces(char **str)
{
	int	len;

	if (!str || !(*str))
		return ;
	len = ft_strlen(*str);
	while (len > 0 && ft_isspace((*str)[len - 1]))
		len--;
	(*str)[len] = '\0';
}

void	ft_init_table(int *t, int n)
{
	int	i;

	i = 0;
	while (i < n)
		t[i++] = 0;
}

int	ft_hash_table(const char *str, int *table)
{
	const char	*ch = str;

	if (table[(unsigned char)*ch] == 0)
		table[(unsigned char)*ch] = 1;
	else
		return (0);
	return (1);
}

void	ft_remove_spaces(char **str)
{
	int	len;

	if (!str || !(*str))
		return ;
	while (ft_isspace(**str))
		(*str)++;
	len = ft_strlen(*str);
	while (len > 0 && ft_isspace((*str)[len - 1]))
		len--;
	(*str)[len] = '\0';
}

int	ft_tern_op(int condition, int true_value, int false_value)
{
	if (condition)
		return (true_value);
	else
		return (false_value);
}
