#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> //printf
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# define WIDTH 1400
# define HEIGHT 1000

typedef struct s_cub3d {
	int			width;
	int			height;
	int			**matrix;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_cub3d;

//mlx_utils.c
void	deal_key(struct mlx_key_data keydata, void *param);
void	initialize_mlx(t_cub3d *mapdata);
void	ft_error(void);

#endif