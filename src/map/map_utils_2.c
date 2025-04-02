#include "cub3d.h"

void	calculate_map_width(t_cub3d *mapdata, int start, int map_lines)
{
	int	k;
	int	len;

	k = 0;
	mapdata->map_width = 0;
	while (k < map_lines)
	{
		len = ft_strlen(mapdata->mapping.area[start + k]);
		if (len > mapdata->map_width)
			mapdata->map_width = len;
		k++;
	}
}

// essa função estava gerando bug, pois a alocação estava errada p/ mapas não retangulares
// agora a alocação é feita com base na maior linha do mapa (e agora a largura é calculada antes da alocação)
// e preenchemos o restante com '9' (ou seja, espaços vazios)
void	allocate_and_copy_map(t_cub3d *mapdata, int start, int map_lines, t_pos pos)
{
	mapdata->map_height = map_lines;
	calculate_map_width(mapdata, start, map_lines);
	mapdata->map = malloc(sizeof(char *) * (map_lines + 1));
	if (!mapdata->map)
		cub_error("Failed to allocate map", mapdata);
	while (pos.y < map_lines)
	{
		mapdata->map[pos.y] = malloc(sizeof(char) * (mapdata->map_width + 1));
		if (!mapdata->map[pos.y])
			cub_error("Map line allocation failed", mapdata);
		pos.x = 0;
		while (pos.x < mapdata->map_width)
		{
			if ((size_t)pos.x < ft_strlen(mapdata->mapping.area[start + pos.y]) \
				&& mapdata->mapping.area[start + pos.y][pos.x] != '\n')
				mapdata->map[pos.y][pos.x] = mapdata->mapping.area[start + pos.y][pos.x];
			else
				mapdata->map[pos.y][pos.x] = '9';
			pos.x++;
		}
		mapdata->map[pos.y][pos.x - 1] = '\n'; // adiciona o \n ao fim da linha não é necessário para o funcionamento do programa, mas ajuda a visualizar o mapa no print de debug
		mapdata->map[pos.y][pos.x] = '\0';
		pos.y++;
	}
	mapdata->map[pos.y] = NULL;
}

// void	calculate_map_dimensions(t_cub3d *mapdata, int map_lines)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	mapdata->map_height = map_lines;
// 	mapdata->map_width = 0;
// 	while (i < map_lines)
// 	{
// 		len = ft_strlen(mapdata->map[i]);
// 		if (len > mapdata->map_width)
// 			mapdata->map_width = len;
// 		i++;
// 	}
// }
