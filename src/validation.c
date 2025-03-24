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

int	cub_valid(t_cub3d *mapdata)
{
	if (!mapdata->cub)
        cub_error("Argument with 'file.cub' is required!");
	if (!cub_file(mapdata->cub))
        cub_error("Incorrect file type. It's not '*.cub'!");

	// game->map.lines = map_lines(game->ber);
	// if (game->map.lines < 3)
	// 	so_error("Invalid Map!");
	// game->map.area = malloc(sizeof(char *) * game->map.lines);
	// if (!game->map.area)
	// 	so_error("Memory Allocation Error!");
	// so_make_area1(game->ber, game->map.lines, game->map.area);
	// so_make_area2(&game->map.area, game->map.lines);
	// game->map.cols = -1;
	// so_check_cols(game->map.area, game->map.lines, game);
	// so_check_walls(game->map.area, game->map.lines, game->map.cols);
	// so_check_characters(game, game->map.lines, game->map.cols);
	// so_valid_path(game, game->map.lines);
	// game->steps = 0;
	// game->score = 0;
	return (1);
}
