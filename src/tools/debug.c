#include "cub3d.h"

void	print_area(char **area)
{
	int	i;

	i = 0;
	while (area[i])
	{
		ft_putstr_fd(area[i], 1);
		// ft_putstr_fd("\n", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

void	print_textures(t_cub3d *mapdata)
{
	ft_putendl_fd(mapdata->texture.no, 1);
	ft_putendl_fd(mapdata->texture.so, 1);
	ft_putendl_fd(mapdata->texture.we, 1);
	ft_putendl_fd(mapdata->texture.ea, 1);
}




//função mapa placeholder
void	init_map(t_cub3d *mapdata)
{
/*responsabilidade futura dessa função
	- parsear mapa e preencher *map na struct do cub3d;
			(pode ser necessário trocar a variável na struct, que é um array de ints)
	- alocar memória para o mapa;
	- preencher map_width;
	- preencher map_height;
	- preencher tile_size;*/
	static char	*local_map[] = {
		"11111111",
		"10101001",
		"10101001",
		"10100001",
		"1000S001",
		"10000101",
		"10000001",
		"11111111"
	};
	mapdata->map_width = 8;
	mapdata->map_height = 8;
	mapdata->tile_size = 64;
	mapdata->map = local_map;
	find_player_start(mapdata);
}
//fim mapa placeholder