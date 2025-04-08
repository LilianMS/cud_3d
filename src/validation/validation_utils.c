#include "cub3d.h"

void	ft_hash_table(int *t, int n)
{
	int	i;

	i = 0;
	while (i < n)
		t[i++] = 0;
}

void	ft_fill_valid_characters(const char *valid_chars, int *table)
{
	const char	*ch = valid_chars;

	while (*ch)
	{
		table[(unsigned char)*ch] = 1;
		ch++;
	}
}

int	cub_search_elements(t_cub3d *mapdata, const char *elements)
{
	int	table[256];

	ft_hash_table(table, 256);
	ft_fill_valid_characters(elements, table);
	if (!check_all_chars(mapdata->mapping.area, elements) \
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
	end++;
	while (area[end])
	{
		x = 0;
		while (area[end] && (area[end][0] == '\n' || area[end][0] == '\0'))
			end++;
		if (area[end] == NULL)
			break ;
		while (area[end][x] && ft_isspace(area[end][x]))
			x++;
		if (area[end][x] && area[end][x] != '\n' && area[end][x] != '\0')
		{
			cub_error("Map is not at the end of the file", mapdata);
			return (0);
		}
		end++;
	}
	return (1);
}
