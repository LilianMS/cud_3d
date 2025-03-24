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

int	cub_read_file(t_cub3d *mapdata)
{
	int		fd;
	char	*line;

	fd = open(mapdata->cub, O_RDONLY);
	if (fd == -1)
		cub_error("Error open file!", mapdata);
	line = get_next_line(fd);
	while (line)
	{
		ft_putstr_fd(line, 1);
		free(line);
		line = get_next_line(fd);
	}
	ft_putstr_fd("\n", 1);
	free(line);
	close(fd);
	return (1);
}

int	cub_valid(t_cub3d *mapdata)
{
	if (!mapdata->cub)
		cub_error("Argument with 'file.cub' is required!", mapdata);
	if (!cub_file(mapdata->cub))
		cub_error("Incorrect file type. It's not '*.cub'!", mapdata);
	cub_read_file(mapdata);
	return (1);
}
