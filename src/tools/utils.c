#include "cub3d.h"

void	cub_error(const char *str, t_cub3d *mapdata)
{
	ft_putstr_fd("Error!\n", 2);
	ft_putstr_fd((char *)str, 2);
	ft_putstr_fd("\n", 2);
	if (mapdata)
		cub_clean(mapdata);
	exit(EXIT_FAILURE);
}

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
