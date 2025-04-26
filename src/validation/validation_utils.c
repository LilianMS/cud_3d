#include "cub3d.h"

void	ft_init_table(int *t, int n)
{
	int	i;

	i = 0;
	while (i < n)
		t[i++] = 0;
}

int	ft_hash_table(const char *valid_chars, int *table)
{
	const char	*ch = valid_chars;

	if (table[(unsigned char)*ch] == 0)
		table[(unsigned char)*ch] = 1;
	else
		return (0);
	return (1);
}

int	check_duplicate(t_cub3d *mapdata, int *tab)
{
	char	**area;
	int		i;

	area = mapdata->mapping.area;
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

int	cub_search_elements(t_cub3d *mapdata, const char *elements)
{
	int	table[256];

	ft_init_table(table, 256);
	if (!check_duplicate(mapdata, table) \
		|| !check_all_chars(mapdata->mapping.area, elements) \
		|| !cub_textures(mapdata) \
		|| !cub_colors(mapdata))
		cub_error("Invalid Map!", mapdata);
	return (1);
}

int	check_map_position(t_cub3d *mapdata, int end)
{
	char	**area;
	int		x;

	area = mapdata->mapping.area;
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
			cub_error("Map is not at the end of the file", mapdata);
			return (0);
		}
		end++;
	}
	return (1);
}
