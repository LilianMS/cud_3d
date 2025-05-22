#include "cub3d.h"

static void	check_size_map(t_cub3d *mapdata, int map_lines)
{
	if (mapdata->map_width > MAX_WIDTH || map_lines > MAX_LINES)
	{
		cub_error("Map size is too big!", mapdata);
	}
	if (mapdata->map_width < MIN_WIDTH || map_lines < MIN_LINES)
	{
		cub_error("Map size is too small!", mapdata);
	}
}

static void	calculate_map_width(t_cub3d *mapdata, int start, int map_lines)
{
	int	k;
	int	len;

	k = 0;
	mapdata->map_height = map_lines;
	mapdata->map_width = 0;
	while (k < map_lines)
	{
		len = ft_strlen(mapdata->mapping.area[start + k]);
		if (len > mapdata->map_width)
			mapdata->map_width = len;
		k++;
	}
	check_size_map(mapdata, map_lines); // validação para tamanho máximo e mínimo do mapa ???
}

// essa função estava gerando bug, pois a alocação estava errada p/ mapas não retangulares
// agora a alocação é feita com base na maior linha do mapa (e agora a largura é calculada antes da alocação)
// e preenchemos o restante com '9' (ou seja, espaços vazios)
void	allocate_copy_map(t_cub3d *data, int init, int lines, t_pos pos)
{
	calculate_map_width(data, init, lines);
	data->map = malloc(sizeof(char *) * (lines + 1));
	if (!data->map)
		cub_error("Failed to allocate map", data);
	while (pos.y < lines)
	{
		data->map[pos.y] = malloc(sizeof(char) * (data->map_width + 1));
		if (!data->map[pos.y])
			cub_error("Map line allocation failed", data);
		pos.x = 0;
		while (pos.x < data->map_width)
		{
			if ((size_t)pos.x < ft_strlen(data->mapping.area[init + pos.y]) \
				&& data->mapping.area[init + pos.y][pos.x] != '\n')
				data->map[pos.y][pos.x] = \
							data->mapping.area[init + pos.y][pos.x];
			else
				data->map[pos.y][pos.x] = '9';
			pos.x++;
		}
		data->map[pos.y][pos.x - 1] = '\n'; // adiciona o \n ao fim da linha não é necessário para o funcionamento do programa, mas ajuda a visualizar o mapa no print de debug
		data->map[pos.y][pos.x] = '\0';
		pos.y++;
	}
	data->map[pos.y] = NULL;
}
