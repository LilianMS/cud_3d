#include "cub3d.h"

// void copy_frame_to_image(mlx_texture_t *texture, mlx_image_t *frame, t_pos pos, int i)
// {
// 	t_cub_img	img;
// 	uint32_t	color;

// 	img = (t_cub_img){0};
// 	while ((uint32_t)pos.y < frame->height)
// 	{
// 		pos.x = 0;
// 		while ((uint32_t)pos.x < frame->width)
// 		{
// 			img.src_x = pos.x + i * frame->width;
// 			img.src_y = pos.y;
// 			img.src_index = (img.src_y * texture->width + img.src_x) * 4;
// 			img.dst_index = (pos.y * frame->width + pos.x) * 4;
// 			img.r = texture->pixels[img.src_index + 0];
// 			img.g = texture->pixels[img.src_index + 1];
// 			img.b = texture->pixels[img.src_index + 2];
// 			img.a = texture->pixels[img.src_index + 3];
// 			color = (img.a << 24) | (img.b << 16) | (img.g << 8) | img.r;
// 			mlx_put_pixel(frame, pos.x, pos.y, color);
// 			pos.x++;
// 		}
// 		pos.y++;
// 	}
// }

// void	extract_torch_frames(t_cub3d *mdata, mlx_texture_t* texture)
// {
// 	mlx_image_t	*frame;
// 	uint32_t	frame_width;
// 	uint32_t	frame_height;
// 	int			i;

// 	frame_width = texture->width / TORCH_FRAMES;
// 	frame_height = texture->height;
// 	i = 0;
// 	while (i < TORCH_FRAMES)
// 	{
// 		frame = mlx_new_image(mdata->mlx, frame_width, frame_height);
// 		if (!frame)
// 			cub_error("Failed to create frame image", mdata);
// 		copy_frame_to_image(texture, frame, (t_pos){0, 0}, i);
// 		mdata->anim.torch_images[i] = frame;
// 		i++;
// 	}
// }

// void	init_t_animation(t_cub3d *mdata)
// {
// 	t_animation	*anim;

// 	anim = &mdata->anim;
// 	anim->torch_frame = 0;
// 	anim->torch_frame_count = TORCH_FRAMES;
// 	anim->timer = 0;
// 	// ft_memset(anim->torch_images, 0, sizeof(anim->torch_images));
// 	anim->torch_texture = mlx_load_png("./assets/textures/torch_spritesheet2.png");
// 	if (!mdata->anim.torch_texture)
// 		cub_error("Failed to load torch texture", mdata);
// 	extract_torch_frames(mdata, mdata->anim.torch_texture);
// }

// void	cub_load_textures_bonus(t_cub3d *mdata)
// {
// 	init_t_animation(mdata);
// 	if (!mdata->mlx)
// 		cub_error("MLX not initialized!", mdata);
//     // Colocar todos os frames na mesma posição da tela
// 	int i = 0;
// 	while (i < TORCH_FRAMES)
// 	{
// 		mlx_image_to_window(mdata->mlx,
// 			mdata->anim.torch_images[i],
// 			(WIDTH / 2) - (mdata->anim.torch_images[i]->width / 2),
// 			HEIGHT - mdata->anim.torch_images[i]->height - 10);
// 			mdata->anim.torch_images[i]->enabled = false; // Começa invisível
// 		i++;
// 	}
//     // Iniciar no frame 0 visível
//     mdata->anim.current_frame = 0;
//     mdata->anim.timer = 0;
//     mdata->anim.torch_images[0]->enabled = true;
// }

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
		set_hud_position(frames[i], -80, 180);
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
		cub_error("Argument with 'file.cub' is required!", NULL);
	mdata = malloc(sizeof(t_cub3d));
	cub_starts(av, mdata);
	initialize_mlx(mdata);
	// cub_load_textures_bonus(mdata);
	if (mdata->minimap_window)
		mlx_loop(mdata->minimap_window);
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
