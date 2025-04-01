#include "cub3d.h"

// int	check_forb_chars(char **area, int *table)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (area[i])
// 	{
// 		j = 0;
// 		while (area[i][j])
// 		{
// 			if (!table[(unsigned char)area[i][j]]
// 				&& area[i][j] != '0')
// 				return (0);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

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
	// checar se o mapa é válido
	// verificar se o mapa é fechado
	// verificar se o mapa tem uma posição inicial UNICA do player
	extract_map_from_area(mapdata);
	find_player_start(mapdata); // encontrar a posição do player
		// - is_valid_player(mapdata); // não ter mais de um player
	//is_valid_map(mapdata);
		// - is_valid_walls(mapdata); // checar se os espaços estão cercados por 1
		// - flood_fill(mapdata); // checar se o mapa é fechado
		// - area_visited(mapdata); // checar se o caminho é válido
	mapdata->tile_size = calculate_tile_size(WIDTH, HEIGHT, \
		mapdata->map_width, \
		mapdata->map_height);
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
	if (!cub_file(mapdata->mapping.file))
		cub_error("Incorrect file type. It's not '*.cub'!", mapdata);
	cub_read_file(mapdata);
	// debug
	// print_area(mapdata->mapping.area);
	// debug
	cub_search_elements(mapdata, "NSWEAOFC");
	cub_check_invalid_chars(mapdata, (t_pos){0, 0});
	cub_read_area(mapdata);
	return (1);
}
