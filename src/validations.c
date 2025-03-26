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
	int		i;

	fd = open(mapdata->mapping.file, O_RDONLY);
	if (fd == -1)
		cub_error("Error open file!", mapdata);
	i = 0;
	mapdata->mapping.area = malloc(sizeof(char *) * MAX_LINES);
	if (!mapdata->mapping.area)
		cub_error("Memory allocation failed!", mapdata);
	mapdata->mapping.area[i] = get_next_line(fd);
	if (!mapdata->mapping.area[i])
		cub_error("Invalid Map!", mapdata);
	mapdata->mapping.lines = 0;
	while (mapdata->mapping.area[i])
	{
		mapdata->mapping.lines++;
		i++;
		mapdata->mapping.area[i] = get_next_line(fd);
	}
	mapdata->mapping.area[i + 1] = NULL;
	close(fd);
	return (1);
}

static void	cub_read_area(t_cub3d *mapdata)
{
	// int	i;

	// i = 0;
	if (!search_elements(mapdata, "NSWEAOFC"))
		cub_error("Invalid Map!", mapdata);
	//
}

int	cub_valid(t_cub3d *mapdata)
{
	if (!mapdata->mapping.file)
		cub_error("Argument with 'file.cub' is required!", mapdata);
	if (!cub_file(mapdata->mapping.file))
		cub_error("Incorrect file type. It's not '*.cub'!", mapdata);
	cub_read_file(mapdata);
	// debug
	// print_area(mapdata->mapping.area);
	// debug
	cub_read_area(mapdata);
	extract_map_from_area(mapdata);
	mapdata->tile_size = calculate_tile_size(WIDTH, HEIGHT, mapdata->map_width, mapdata->map_height);
	find_player_start(mapdata);
	return (1);
}
