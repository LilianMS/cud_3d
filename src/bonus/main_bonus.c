/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:48:50 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/26 23:24:14 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_load_textures_bonus(t_cub3d *mdata)
{
	mlx_texture_t	*tx;
	mlx_image_t		**frames;
	int				i;

	if (!mdata->mlx)
		cub_error("MLX not initialized!", mdata);
	tx = mlx_load_png("./assets/textures/torch_spritesheet.png");
	if (!tx)
		cub_error("Failed to load torch texture", mdata);
	frames = extract_frames(mdata->mlx, tx, TORCH_FRAMES);
	mlx_delete_texture(tx);
	if (!frames)
		cub_error("Failed to extract torch frames", mdata);
	init_animation(&mdata->anim.torch, mdata->mlx, frames, 0.15);
	i = 0;
	while (i < TORCH_FRAMES)
	{
		set_hud_position(frames[i], 180, 320);
		i++;
	}
}

void	cub_load_textures(t_cub3d *mdata)
{
	mdata->texture.north = mlx_load_png(mdata->texture.no);
	if (!mdata->texture.north)
		cub_error("Error loading north texture!", mdata);
	mdata->texture.south = mlx_load_png(mdata->texture.so);
	if (!mdata->texture.south)
		cub_error("Error loading south texture!", mdata);
	mdata->texture.west = mlx_load_png(mdata->texture.we);
	if (!mdata->texture.west)
		cub_error("Error loading west texture!", mdata);
	mdata->texture.east = mlx_load_png(mdata->texture.ea);
	if (!mdata->texture.east)
		cub_error("Error loading east texture!", mdata);
}

int	cub_starts(char **av, t_cub3d *mdata)
{
	if (!mdata)
		cub_error("Memory allocation error.", NULL);
	ft_memset(mdata, 0, sizeof(t_cub3d));
	mdata->mapping.file = av[1];
	mdata->fov = M_PI / 3.0;
	cub_valid(mdata);
	cub_load_textures(mdata);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	*mdata;

	if (ac != 2)
		cub_error("Error: bad arguments", NULL);
	mdata = malloc(sizeof(t_cub3d));
	cub_starts(av, mdata);
	initialize_mlx(mdata);
	cub_load_textures_bonus(mdata);
	init_minimap(mdata);
	mlx_loop(mdata->mlx);
	mdata->passed = 1;
	cub_clean(mdata);
	mlx_terminate(mdata->mlx);
	if (mdata)
		free(mdata);
	return (0);
}
