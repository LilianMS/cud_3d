#include "cub3d.h"

int	calculate_tile_size(int screen_width, int screen_height, int map_width, int map_height)
{
	int	tile_w = screen_width / map_width;
	int	tile_h = screen_height / map_height;
	return (tile_w < tile_h) ? tile_w : tile_h;
}


int	is_map_line(char *line)
{
	int	i;

	if (!line || line[0] == '\n') // Linha só com \n?
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			i++;
			continue;
		}
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}


void	extract_map_from_area(t_cub3d *mapdata)
{
	int		start;
	int		end;
	int		i;
	int		map_lines;

	start = 0;
	end = 0;
	i = 0;
	map_lines = 0;
	//Encontrar início do mapa
	while (mapdata->mapping.area[start] && !is_map_line(mapdata->mapping.area[start]))
		start++;
	if (!mapdata->mapping.area[start])
		cub_error("Map not found in file!", mapdata);
	//Encontrar fim do mapa
	end = start;
	while (mapdata->mapping.area[end] && is_map_line(mapdata->mapping.area[end]))
		end++;
	//Calcular quantidade de linhas de mapa
	map_lines = end - start;
	//Alocar e copiar
	mapdata->map = malloc(sizeof(char *) * (map_lines + 1));
	if (!mapdata->map)
		cub_error("Failed to allocate map", mapdata);
	i = 0;
	while (i < map_lines)
	{
		mapdata->map[i] = ft_strdup(mapdata->mapping.area[start + i]);
		if (!mapdata->map[i])
			cub_error("Map line allocation failed", mapdata);
		i++;
	}
	mapdata->map[i] = NULL;
	//Calcular dimensões
	mapdata->map_height = map_lines;
	mapdata->map_width = 0;
	i = 0;
	while (i < map_lines)
	{
		int len = ft_strlen(mapdata->map[i]);
		if (len > mapdata->map_width)
			mapdata->map_width = len;
		i++;
	}
}
