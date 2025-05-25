/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:51:35 by lilmende          #+#    #+#             */
/*   Updated: 2025/05/25 16:51:36 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		cub_error("Argument with 'file.cub' is required!", NULL);
	mdata = malloc(sizeof(t_cub3d));
	cub_starts(av, mdata);
	initialize_mlx(mdata);
	mlx_loop(mdata->mlx);
	cub_clean(mdata);
	mlx_terminate(mdata->mlx);
	if (mdata)
		free(mdata);
	return (0);
}

/*
 ** To run with Valgrind and suppressions:
 *** valgrind --suppressions=mlx42.supp ./cub3D assets/map/simple_map.cub
 ** For detailed analysis:
 *** valgrind --leak-check=full --show-leak-kinds=all
 *** --suppressions=mlx42.supp ./cub3D assets/map/simple_map.cub
 */
