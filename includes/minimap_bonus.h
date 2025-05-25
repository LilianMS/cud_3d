/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:36 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/25 17:10:16 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

# include "cub3d.h"

void	init_minimap(t_cub3d *mdata);
void	draw_minimap_static(t_cub3d *mdata);
void	update_minimap_dynamic(t_cub3d *mdata);
void	clear_minimap_dynamic(t_cub3d *mdata);
void	render_player_on_minimap(t_cub3d *mdata);
void	render_direction_on_minimap(t_cub3d *mdata);

#endif
