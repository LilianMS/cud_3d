#ifndef ANIMATION_H
# define ANIMATION_H

# include "../lib/MLX42/include/MLX42/MLX42.h" 
# define TORCH_FRAMES 4

typedef struct s_animation
{
	mlx_image_t	**frames;
	int			frame_count;
	int			current_frame;
	double		timer;
	double		frame_duration;
	int			x;
	int			y;
}	t_animation;

typedef struct s_animations
{
	t_animation	torch;
}	t_animations;

mlx_image_t	**extract_frames(mlx_t *mlx, mlx_texture_t *tx, int frames);
void		copy_texture_to_image(mlx_texture_t *tx, mlx_image_t *img,
				int idx, uint32_t fw);
void		init_animation(t_animation *anim, mlx_t *mlx,
				mlx_image_t **frames, double frame_duration);
void		update_animation(t_animation *anim, double delta_time);
void		set_hud_position(mlx_image_t *img, int offset_x, int offset_y);
void		destroy_frames(mlx_t *mlx, mlx_image_t **frames, int frame_count);

#endif
