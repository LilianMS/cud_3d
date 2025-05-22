#include "cub3d.h"

static void	get_texture_point(t_cub3d *game)
{
	game->render.texture_x = (int)(game->render.wall_point * game->texture.curr->width);
	if ((game->render.side == 0 && game->render.ray_dir_x < 0) || (game->render.side == 1 && game->render.ray_dir_y > 0))
		game->render.texture_x = game->texture.curr->width - game->render.texture_x - 1;
	game->render.resize = 1.0 * game->texture.curr->height / game->render.line_height;
}

static void	set_wall_point(t_cub3d *game)
{
	double	wall_point;

	if (game->render.side == 0)
	{
		wall_point = (game->player_y / game->tile_size) + game->render.perp_wall_dist
			* game->render.ray_dir_y;
	}
	else
	{
		wall_point = (game->player_x / game->tile_size) + game->render.perp_wall_dist
			* game->render.ray_dir_x;
	}
	game->render.wall_point = wall_point - floor(wall_point);
}

void	cub_draw_column_slice(t_cub3d *mapdata, int x)
{
	int		y;
	int		tex_y;
	uint32_t	color;

	mapdata->render.line_height = (int)(HEIGHT / mapdata->render.perp_wall_dist);
	mapdata->render.draw_start = -mapdata->render.line_height / 2 + HEIGHT / 2;
	mapdata->render.draw_end = mapdata->render.line_height / 2 + HEIGHT / 2;
	if (mapdata->render.draw_start < 0)
		mapdata->render.draw_start = 0;
	if (mapdata->render.draw_end >= HEIGHT)
		mapdata->render.draw_end = HEIGHT - 1;
	// Captura a textura correta para a parede (norte, sul, leste, oeste)
	cub_capture_texture(mapdata);
	// Calcula a posição X da textura
	set_wall_point(mapdata);
	get_texture_point(mapdata);
	mapdata->render.texture_pos = (mapdata->render.draw_start - HEIGHT / 2 + mapdata->render.line_height / 2) * mapdata->render.resize;
	y = mapdata->render.draw_start;
	while (y < mapdata->render.draw_end)
	{
		// Calcula a posição Y correspondente na textura
		tex_y = (int)mapdata->render.texture_pos;
		if(tex_y < 0)
			tex_y = 0;
		if(tex_y >= (int)mapdata->texture.curr->height)
			tex_y = (int)mapdata->texture.curr->height - 1;
		mapdata->render.texture_pos += mapdata->render.resize;
		// Pega a cor da textura
		color = cub_get_texture_pixel(mapdata->texture.curr, mapdata->render.texture_x, tex_y);
		// Desenha o pixel no framebuffer
		mlx_put_pixel(mapdata->img, x, y, color);
		y++;
	}
}
