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
