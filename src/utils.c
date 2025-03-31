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

void	remove_newline(char ***colors)
{
	int	i;

	i = 0;
	while ((*colors)[i])
	{
		char *newline = ft_strchr((*colors)[i], '\n');
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
