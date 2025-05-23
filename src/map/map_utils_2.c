#include "cub3d.h"

static void	check_size_map(t_cub3d *mdata, int map_lines)
{
	if (mdata->map_width > MAX_WIDTH || map_lines > MAX_LINES)
	{
		cub_error("Map size is too big!", mdata);
	}
	if (mdata->map_width < MIN_WIDTH || map_lines < MIN_LINES)
	{
		cub_error("Map size is too small!", mdata);
	}
}

static void	calculate_map_width(t_cub3d *mdata, int start, int map_lines)
{
	int	k;
	int	len;

	k = 0;
	mdata->map_height = map_lines;
	mdata->map_width = 0;
	while (k < map_lines)
	{
		len = ft_strlen(mdata->mapping.area[start + k]);
		if (len > mdata->map_width)
			mdata->map_width = len;
		k++;
	}
	check_size_map(mdata, map_lines); // validação para tamanho máximo e mínimo do mapa ???
}

// essa função estava gerando bug, pois a alocação estava errada p/ mapas não retangulares
// agora a alocação é feita com base na maior linha do mapa (e agora a largura é calculada antes da alocação)
// e preenchemos o restante com '9' (ou seja, espaços vazios)
void	allocate_copy_map(t_cub3d *mdata, int init, int lines, t_pos pos)
{
	calculate_map_width(mdata, init, lines);
	mdata->map = malloc(sizeof(char *) * (lines + 1));
	if (!mdata->map)
		cub_error("Failed to allocate map", mdata);
	while (pos.y < lines)
	{
		mdata->map[pos.y] = malloc(sizeof(char) * (mdata->map_width + 1));
		if (!mdata->map[pos.y])
			cub_error("Map line allocation failed", mdata);
		pos.x = 0;
		while (pos.x < mdata->map_width)
		{
			if ((size_t)pos.x < ft_strlen(mdata->mapping.area[init + pos.y]) \
				&& mdata->mapping.area[init + pos.y][pos.x] != '\n')
				mdata->map[pos.y][pos.x] = \
							mdata->mapping.area[init + pos.y][pos.x];
			else
				mdata->map[pos.y][pos.x] = '9';
			pos.x++;
		}
		mdata->map[pos.y][pos.x - 1] = '\n'; // adiciona o \n ao fim da linha não é necessário para o funcionamento do programa, mas ajuda a visualizar o mapa no print de debug
		mdata->map[pos.y][pos.x] = '\0';
		pos.y++;
	}
	mdata->map[pos.y] = NULL;
}
