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

int	check_forb_chars(char **area, int *table)
{
	int	i;
	int	j;

	i = 0;
	while (area[i])
	{
		j = 0;
		while (area[i][j])
		{
			if (!table[(unsigned char)area[i][j]]
				&& area[i][j] != '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	search_elements(t_cub3d *mapdata, const char *elements)
{
	int	table[256];

	ft_hash_table(table, 256);
	ft_fill_valid_characters(elements, table);
	if (!check_all_chars(mapdata->mapping.area, elements))
		return (0);
	cub_textures(mapdata);
	//debug
	print_textures(mapdata);
	// debug
	return (1);
}
