#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

void	init_minimap(t_cub3d *mdata);
void	draw_minimap_static(t_cub3d *mdata);
void	update_minimap_dynamic(t_cub3d *mdata);
void	clear_minimap_dynamic(t_cub3d *mdata);
void	render_player_on_minimap(t_cub3d *mdata);
void	render_direction_on_minimap(t_cub3d *mdata);

#endif
