#include "animation.h"
#include "cub3d.h"

void	set_hud_position(mlx_image_t *img, int offset_x, int offset_y)
{
	img->instances[0].x = (WIDTH / 2) - (img->width / 2) + offset_x;
	img->instances[0].y = HEIGHT - img->height + offset_y;
	// img->instances[0].z = 0; // Z depth can be adjusted if needed
	// img->enabled = true; // Ensure the image is enabled for rendering
}
