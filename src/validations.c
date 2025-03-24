#include "cub3d.h"

static int	cub_file(char *str)
{
	char	*cub;
	int		len;
	int		i;

	cub = ".cub";
	i = ft_strlen(cub) - 1;
	len = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[len--] != cub[i--])
			return (0);
	}
	return (1);
}

int	cub_valid(t_cub3d *mapdata)
{
	if (!mapdata->cub)
        cub_error("Argument with 'file.cub' is required!");
	if (!cub_file(mapdata->cub))
        cub_error("Incorrect file type. It's not '*.cub'!");

	return (1);
}
