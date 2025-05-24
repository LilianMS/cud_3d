#include "cub3d.h"

void	free_area(char **area)
{
	int	i;

	i = 0;
	while (area[i])
	{
		free(area[i]);
		i++;
	}
	free(area);
}

void	cub_free_data(t_cub3d *mdata)
{
	if (mdata->texture.north)
		mlx_delete_texture(mdata->texture.north);
	if (mdata->texture.south)
		mlx_delete_texture(mdata->texture.south);
	if (mdata->texture.west)
		mlx_delete_texture(mdata->texture.west);
	if (mdata->texture.east)
		mlx_delete_texture(mdata->texture.east);
	if (mdata->texture.no)
		free(mdata->texture.no);
	if (mdata->texture.so)
		free(mdata->texture.so);
	if (mdata->texture.we)
		free(mdata->texture.we);
	if (mdata->texture.ea)
		free(mdata->texture.ea);
	if (mdata->tmp)
		free(mdata->tmp);
	if (mdata->anim.torch.frames)
		destroy_frames(mdata->mlx, mdata->anim.torch.frames, \
			mdata->anim.torch.frame_count);

}

void	cub_clean(t_cub3d *mdata)
{
	cub_free_data(mdata);
	if (mdata->flood_map)
		free_area(mdata->flood_map);
	if (mdata->mapping.area)
		free_area(mdata->mapping.area);
	if (mdata->map)
		free_area(mdata->map);
}
