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

int	ft_str_is_space(const char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*handle_textures(int dir, char *str)
{
	char	*texture;
	char	*tmp_str;
	int		i;
	int		j;

	tmp_str = ft_strchr(str, dir);
	if (!tmp_str || ft_str_is_space(tmp_str + 2))
		return (NULL);
	tmp_str += 2;
	texture = malloc(sizeof(char) * (ft_strlen(tmp_str) + 1));
	if (!texture)
		return (NULL);
	i = 0;
	while (ft_isspace(tmp_str[i]))
		i++;
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

#include <fcntl.h>

char	*get_invalid_texture_file(t_cub3d *mapdata)
{
	char	*invalid_file;
	int		fd;

	invalid_file = NULL;
	fd = open(mapdata->texture.no, O_RDONLY);
	if (!ft_check_kind_file(mapdata->texture.no, ".png") || fd < 0)
		invalid_file = mapdata->texture.no;
	else
		close(fd);
	fd = open(mapdata->texture.so, O_RDONLY);
	if (!ft_check_kind_file(mapdata->texture.so, ".png") || fd < 0)
		invalid_file = mapdata->texture.so;
	else
		close(fd);
	fd = open(mapdata->texture.we, O_RDONLY);
	if (!ft_check_kind_file(mapdata->texture.we, ".png") || fd < 0)
		invalid_file = mapdata->texture.we;
	else
		close(fd);
	fd = open(mapdata->texture.ea, O_RDONLY);
	if (!ft_check_kind_file(mapdata->texture.ea, ".png") || fd < 0)
		invalid_file = mapdata->texture.ea;
	else
		close(fd);
	return (invalid_file);
}

void	check_file_texture(t_cub3d *mapdata)
{
	const char	*msg = "Invalid file!";
	char		*invalid_file;

	invalid_file = get_invalid_texture_file(mapdata);
	if (invalid_file)
	{
		mapdata->tmp = ft_strjoin(msg, invalid_file);
		if (mapdata->tmp)
			cub_error(mapdata->tmp, mapdata);
		else
			cub_error(msg, mapdata);
	}
}

int	cub_textures(t_cub3d *mapdata)
{
	char	**area;
	int		i;

	area = mapdata->mapping.area;
	i = 0;
	while (area[i])
	{
		if (ft_strncmp(area[i], "NO", 2) == 0)
			mapdata->texture.no = handle_textures('N', area[i]);
		else if (ft_strncmp(area[i], "SO", 2) == 0)
			mapdata->texture.so = handle_textures('S', area[i]);
		else if (ft_strncmp(area[i], "WE", 2) == 0)
			mapdata->texture.we = handle_textures('W', area[i]);
		else if (ft_strncmp(area[i], "EA", 2) == 0)
			mapdata->texture.ea = handle_textures('E', area[i]);
		i++;
	}
	if (!mapdata->texture.no || !mapdata->texture.so \
		|| !mapdata->texture.we || !mapdata->texture.ea)
	{
		cub_error("Invalid textures!", mapdata);
		return (0);
	}
	check_file_texture(mapdata);
	return (1);
}
