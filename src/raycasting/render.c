#include "cub3d.h"
#include <math.h>
#include <stdio.h>

// Valor grande para evitar divisão por zero.
#define VERY_BIG 1e30

static void clear_3d_render(t_cub3d *mapdata)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(mapdata->img, x, y, 0x333333FF);
			y++;
		}
		x++;
	}
}

//DDA - descobre onde o raio bateu (e se vert ou hor) e retorna a distância perpendicular
static void cast_single_ray(t_cub3d *mapdata, double rayAngle, double *perpWallDist, int *side)
{
    double rayDirX = cos(rayAngle);
    double rayDirY = -sin(rayAngle);
    int mapX = (int)(mapdata->player_x / mapdata->tile_size);
    int mapY = (int)(mapdata->player_y / mapdata->tile_size);

    // deltaDistX / deltaDistY
    double deltaDistX = (rayDirX == 0) ? VERY_BIG : fabs(1.0 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? VERY_BIG : fabs(1.0 / rayDirY);

    // stepX, stepY, sideDistX, sideDistY
    int stepX = (rayDirX < 0) ? -1 : 1;
    *side = 0; // por precaução, inicializamos
    double sideDistX = (rayDirX < 0)
        ? (mapdata->player_x / mapdata->tile_size - mapX) * deltaDistX
        : (mapX + 1.0 - mapdata->player_x / mapdata->tile_size) * deltaDistX;

    int stepY = (rayDirY < 0) ? -1 : 1;
    double sideDistY = (rayDirY < 0)
        ? (mapdata->player_y / mapdata->tile_size - mapY) * deltaDistY
        : (mapY + 1.0 - mapdata->player_y / mapdata->tile_size) * deltaDistY;

    // DDA loop
    int hit = 0;
    while (!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            *side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            *side = 1;
        }
        if (mapY < 0 || mapY >= mapdata->map_height || mapX < 0 || mapX >= mapdata->map_width)
            hit = 1; // saiu do mapa
        else if (mapdata->map[mapY][mapX] == '1')
            hit = 1;
    }

    // Distância perpendicular
    if (*side == 0)
        *perpWallDist = (mapX - (mapdata->player_x / mapdata->tile_size)
                        + (1 - stepX) / 2.0) / rayDirX;
    else
        *perpWallDist = (mapY - (mapdata->player_y / mapdata->tile_size)
                        + (1 - stepY) / 2.0) / rayDirY;

    if (*perpWallDist < 0.0001)
        *perpWallDist = 0.0001;
}

//faz o desenho de uma linha vertical
static void draw_column_slice(t_cub3d *mapdata, int x, double perpWallDist, int side)
{
    int lineHeight = (int)(HEIGHT / perpWallDist);
    int drawStart = (-lineHeight / 2) + (HEIGHT / 2);
    int drawEnd = (lineHeight / 2) + (HEIGHT / 2);

    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;

    // Escolhe cor (diferente se horizontal ou vertical)
    unsigned int wallColor = 0xFFFF00FF; // amarelo
    if (side == 1)
        wallColor = 0xFFAA00FF; // laranja

    // Desenha pixel a pixel
    int y = drawStart;
    while (y < drawEnd)
    {
        mlx_put_pixel(mapdata->img, x, y, wallColor);
        y++;
    }
}

void render_3d(t_cub3d *mapdata)
{
    clear_3d_render(mapdata);

    int x = 0;
    while (x < WIDTH)
    {
        double cameraX = 2.0 * x / (double)WIDTH - 1.0;
        double rayAngle = mapdata->player_angle - cameraX * (FOV / 2.0);

        double perpWallDist;
        int side;
        cast_single_ray(mapdata, rayAngle, &perpWallDist, &side);

        draw_column_slice(mapdata, x, perpWallDist, side);
        x++;
    }
}
