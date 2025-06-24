/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:50 by lilmende          #+#    #+#             */
/*   Updated: 2025/06/24 08:12:27 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*handle_textures(int dir, char *str)
{
	char	*texture;
	char	*tmp_str;
	int		i;
	int		j;

	tmp_str = ft_strchr(str, dir);
	if (!tmp_str)
		return (NULL);
	tmp_str += 2;
	texture = malloc(sizeof(char) * (ft_strlen(tmp_str) + 1));
	if (!texture)
		return (NULL);
	i = 0;
	while (ft_isspace(tmp_str[i]))
		i++;
	ft_remove_end_spaces(&tmp_str);
	j = 0;
	while (tmp_str[i])
	{
		if (tmp_str[i] != '\n')
			texture[j++] = tmp_str[i];
		i++;
	}
	texture[j] = '\0';
	return (texture);
}

char	*get_invalid_texture_file(t_cub3d *mdata)
{
	char	*invalid_file;
	int		fd;

	invalid_file = NULL;
	fd = open(mdata->texture.no, O_RDONLY);
	if (!ft_check_kind_file(mdata->texture.no, ".png") || fd < 0)
		invalid_file = mdata->texture.no;
	else
		close(fd);
	fd = open(mdata->texture.so, O_RDONLY);
	if (!ft_check_kind_file(mdata->texture.so, ".png") || fd < 0)
		invalid_file = mdata->texture.so;
	else
		close(fd);
	fd = open(mdata->texture.we, O_RDONLY);
	if (!ft_check_kind_file(mdata->texture.we, ".png") || fd < 0)
		invalid_file = mdata->texture.we;
	else
		close(fd);
	fd = open(mdata->texture.ea, O_RDONLY);
	if (!ft_check_kind_file(mdata->texture.ea, ".png") || fd < 0)
		invalid_file = mdata->texture.ea;
	else
		close(fd);
	return (invalid_file);
}

void	check_file_texture(t_cub3d *mdata)
{
	const char	*msg = "Invalid file!";
	char		*invalid_file;

	invalid_file = get_invalid_texture_file(mdata);
	if (invalid_file)
	{
		mdata->tmp = ft_strjoin(msg, invalid_file);
		if (mdata->tmp)
			cub_error(mdata->tmp, mdata);
		else
			cub_error(msg, mdata);
	}
}

int	cub_textures(t_cub3d *mdata, int i)
{
	char	**area;
	int		j;

	area = mdata->mapping.area;
	while (area[i])
	{
		spaces_before_data(mdata, i, &j);
		if (ft_strncmp(&area[i][j], "NO", 2) == 0)
			mdata->texture.no = handle_textures('N', &area[i][j]);
		else if (ft_strncmp(&area[i][j], "SO", 2) == 0)
			mdata->texture.so = handle_textures('S', &area[i][j]);
		else if (ft_strncmp(&area[i][j], "WE", 2) == 0)
			mdata->texture.we = handle_textures('W', &area[i][j]);
		else if (ft_strncmp(&area[i][j], "EA", 2) == 0)
			mdata->texture.ea = handle_textures('E', &area[i][j]);
		i++;
	}
	if (!mdata->texture.no || !mdata->texture.so \
		|| !mdata->texture.we || !mdata->texture.ea)
	{
		cub_error("Invalid textures!", mdata);
		return (0);
	}
	check_file_texture(mdata);
	return (1);
}
