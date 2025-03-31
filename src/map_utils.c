#include "cub3d.h"

int	calculate_tile_size(int screen_width, int screen_height, \
						int map_width, int map_height)
{
	int	tile_w;
	int	tile_h;

	tile_w = screen_width / map_width;
	tile_h = screen_height / map_height;
	if (tile_w < tile_h)
		return (tile_w);
	else
		return (tile_h);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || line[0] == '\n')
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			i++;
			continue ;
		}
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	find_map_start(char **area)
{
	int	start;

	start = 0;
	while (area[start] && !is_map_line(area[start]))
		start++;
	if (area[start])
		return (start);
	else
		return (-1);
}

static int	find_map_end(char **area, int start)
{
	int	end;

	end = start;
	while (area[end] && is_map_line(area[end]))
		end++;
	return (end);
}

void	extract_map_from_area(t_cub3d *mapdata)
{
	int	start;
	int	end;
	int	map_lines;

	start = find_map_start(mapdata->mapping.area);
	if (start == -1)
		cub_error("Map not found in file!", mapdata);
	end = find_map_end(mapdata->mapping.area, start);
	map_lines = end - start;
	check_map_position(mapdata, end); // Checa posição do mapa --->> ?! verificar se é necessário
	allocate_and_copy_map(mapdata, start, map_lines);
	calculate_map_dimensions(mapdata, map_lines);
}
