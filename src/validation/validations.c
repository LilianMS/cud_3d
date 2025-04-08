#include "cub3d.h"

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
	cub_extract_map(mapdata); // extrai o mapa e calcula dimensões ---- OK
	cub_player_validation(mapdata, (t_pos){0, 0});
	mapdata->tile_size = calculate_tile_size(WIDTH, HEIGHT, \
												mapdata->map_width, \
												mapdata->map_height);
	cub_map_validation(mapdata, mapdata->p_pos);
	find_player_start(mapdata); // seta a posição do player
}

int	cub_check_invalid_chars(t_cub3d *mapdata, t_pos pos)
{
	char	**a;

	a = mapdata->mapping.area;
	while (a[pos.y])
	{
		pos.x = 0;
		if (ft_strchr("EWNSFC", a[pos.y][pos.x]))
			pos.y++;
		while (a[pos.y] && ft_isspace(a[pos.y][pos.x]))
			pos.x++;
		if (a[pos.y] && ft_strchr("01", a[pos.y][pos.x]))
		{
			while (a[pos.y][pos.x] && ft_strchr("01NSEW ", a[pos.y][pos.x]))
				pos.x++;
			if (a[pos.y][pos.x] == '\0' || a[pos.y][pos.x] == '\n')
				pos.y++;
			else
				cub_error("Invalid character in map!", mapdata);
		}
		else if (a[pos.y] && !ft_strchr("EWNSFC", a[pos.y][pos.x]))
			cub_error("Invalid character in map!", mapdata);
		else
			pos.y++;
	}
	return (1);
}

int	cub_valid(t_cub3d *mapdata)
{
	if (!mapdata->mapping.file)
		cub_error("Argument with 'file.cub' is required!", mapdata);
	if (!ft_check_kind_file(mapdata->mapping.file, ".cub"))
		cub_error("Incorrect file type. It's not '*.cub'!", mapdata);
	cub_read_file(mapdata);
	cub_search_elements(mapdata, "NSWEAOFC");
	cub_check_invalid_chars(mapdata, (t_pos){0, 0});
	cub_read_area(mapdata);
	return (1);
}
