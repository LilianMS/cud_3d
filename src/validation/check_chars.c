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

char	*handle_textures(int dir, char *str)
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
	while (tmp_str[i] == ' ')
		i++;
	j = 0;
	while (tmp_str[i])
	{
		if (tmp_str[i] != ' ' && tmp_str[i] != '\n')
			texture[j++] = tmp_str[i];
		i++;
	}
	texture[j] = '\0';
	return (texture);
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
	if (!mapdata->texture.no || !mapdata->texture.so
		|| !mapdata->texture.we || !mapdata->texture.ea)
	{
		cub_error("Invalid textures!", mapdata);
		return (0);
	}
	return (1);
}
