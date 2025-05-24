#include "animation.h"
#include "cub3d.h"

void	copy_texture_to_image(mlx_texture_t *tx, mlx_image_t *img,
			int idx, uint32_t fw)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	src;
	uint32_t	color;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			src = ((y * tx->width) + x + idx * fw) * 4;
			color = (tx->pixels[src + 3] << 24)
				| (tx->pixels[src + 2] << 16)
				| (tx->pixels[src + 1] << 8)
				| tx->pixels[src + 0];
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

mlx_image_t	**extract_frames(mlx_t *mlx, mlx_texture_t *tx, int frames)
{
	mlx_image_t	**out;
	uint32_t	fw;
	uint32_t	fh;
	int			i;

	fw = tx->width / frames;
	fh = tx->height;
	out = malloc(sizeof(mlx_image_t *) * frames);
	if (!out)
		return (NULL);
	i = -1;
	while (++i < frames)
	{
		out[i] = mlx_new_image(mlx, fw, fh);
		if (!out[i])
			return (NULL);
		copy_texture_to_image(tx, out[i], i, fw);
	}
	return (out);
}

void	init_animation(t_animation *anim, mlx_t *mlx, mlx_image_t **frames,
			double frame_duration)
{
	int	i;

	anim->frames = frames;
	anim->frame_count = 4;
	anim->current_frame = 0;
	anim->timer = 0;
	anim->frame_duration = frame_duration;
	i = 0;
	while (i < anim->frame_count)
	{
		mlx_image_to_window(mlx, anim->frames[i], 0, 0);
		anim->frames[i]->enabled = false;
		i++;
	}
	anim->frames[0]->enabled = true;
}

void	update_animation(t_animation *anim, double delta_time)
{
	if (!anim)
		return ;
	anim->timer += delta_time;
	if (anim->timer >= anim->frame_duration)
	{
		anim->frames[anim->current_frame]->enabled = false;
		anim->current_frame = (anim->current_frame + 1) % anim->frame_count;
		anim->frames[anim->current_frame]->enabled = true;
		anim->timer = 0;
	}
}

void	set_hud_position(mlx_image_t *img, int offset_x, int offset_y)
{
	img->instances[0].x = (WIDTH / 2) - (img->width / 2) + offset_x;
	img->instances[0].y = HEIGHT - img->height + offset_y;
	// img->instances[0].z = 0; // Z depth can be adjusted if needed
	// img->enabled = true; // Ensure the image is enabled for rendering
}

void	destroy_frames(mlx_t *mlx, mlx_image_t **frames, int frame_count)
{
	int i;

	if (!frames)
		return ;
	i = 0;
	while (i < frame_count)
	{
		if (frames[i])
			mlx_delete_image(mlx, frames[i]);
		i++;
	}
	free(frames);
}
