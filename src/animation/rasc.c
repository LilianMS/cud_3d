#include "cub3d.h"

typedef struct s_animation
{
    mlx_texture_t   *torch_texture;
    mlx_image_t     *torch_images[TORCH_FRAMES];
	int			    torch_frame;
	int			    torch_frame_count;
}	t_animation;


void generate_path_wth_id(char *path, const char *str, size_t size, int id)
{
    if (path && size > 0)
    {
        ft_strlcpy(path, str, size);
        ft_strlcat(path, ft_itoa(id), size);
        ft_strlcat(path, ".png", size);
    }
}

void load_torch_frames(t_animation *anim, t_cub3d *mdata)
{
    const char  *str_path = "img/torch_";
    char        path[64];
    int         i;

    anim->torch_frame = 0;
    anim->torch_frame_count = TORCH_FRAMES;
    i = 0;
    while (i < TORCH_FRAMES)
    {
       generate_path_wth_id(path, str_path, sizeof(path), i);
        anim->torch_frames[i] = mlx_load_png(path);
        if (!anim->torch_frames[i])
            cub_error("Failed to load torch texture", mdata);
        anim->torch_images[i] = mlx_texture_to_image(mdata->mlx, anim->torch_frames[i]);
        if (!anim->torch_images[i])
            cub_error("Failed to create torch image from texture", mdata);
        i++;
    }
}

 // snprintf(path, sizeof(path), "textures/torch_%d.png", i);

 mlx_texture_t* torch_texture = mlx_load_png("textures/torch_spritesheet.png");


void extract_torch_frames(mlx_t* mlx, mlx_texture_t* texture) {
    uint32_t frame_width = texture->width / TORCH_FRAMES;
    uint32_t frame_height = texture->height;

    for (uint32_t i = 0; i < TORCH_FRAMES; i++) {
        // Alocar memória para o frame
        uint8_t* pixels = malloc(frame_width * frame_height * sizeof(uint32_t));
        if (!pixels)
            exit(EXIT_FAILURE);

        // Copiar os pixels de cada frame
        for (uint32_t y = 0; y < frame_height; y++) {
            for (uint32_t x = 0; x < frame_width; x++) {
                uint32_t src_index = (y * texture->width + (x + i * frame_width)) * 4;
                uint32_t dst_index = (y * frame_width + x) * 4;

                pixels[dst_index + 0] = texture->pixels[src_index + 0]; // R
                pixels[dst_index + 1] = texture->pixels[src_index + 1]; // G
                pixels[dst_index + 2] = texture->pixels[src_index + 2]; // B
                pixels[dst_index + 3] = texture->pixels[src_index + 3]; // A
            }
        }

        // Criar textura e imagem do frame
        mlx_texture_t* frame_texture = mlx_new_texture(mlx, frame_width, frame_height);
        mlx_texture_to_pixels(frame_texture, pixels);

        torch_frames[i] = mlx_texture_to_image(mlx, frame_texture);

        mlx_delete_texture(frame_texture);
        free(pixels);
    }
}
