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

int	check_map_position(t_cub3d *mapdata, int end)
{
	end++;
	if (mapdata->mapping.area[end] \
		&& !is_map_line(mapdata->mapping.area[end]) \
		&& mapdata->mapping.area[end][0] != '\n' \
		&& mapdata->mapping.area[end][0] != '\0'
		&& mapdata->mapping.area[end][0] != ' ')
	{
		cub_error("The map is NOT in the last position of the file", mapdata);
		return (0);
	}
	return (1);
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
	
	//debug
	// print_textures(mapdata);
	// debug
	return (1);
}
