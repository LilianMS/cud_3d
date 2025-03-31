#include "cub3d.h"

static int	validate_color_values(char **colors)
{
	const char	*str;
	int			i;
	int			value;

	i = 0;
	while (i < 3)
	{
		str = colors[i];
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (0);
			str++;
		}
		value = ft_atoi(colors[i]);
		if (value && (value < 0 || value > 255))
			return (0);
		i++;
	}
	return (1);
}

static char	**cub_handle_colors(t_cub3d *mapdata, int i)
{
	char	**colors;

	colors = ft_split(mapdata->mapping.area[i] + 2, ',');
	remove_newline(&colors);
	if (colors)
	{
		if (ft_array_len(colors) != 3 || !validate_color_values(colors))
		{
			ft_free_split(colors);
			return (NULL);
		}
		return (colors);
	}
	return (NULL);
}

static int	check_color_data(t_cub3d *mapdata)
{
	char	**colors;
	int		i;

	i = 0;
	while (mapdata->mapping.area[i])
	{
		if (mapdata->mapping.area[i][0] == 'F' \
			|| mapdata->mapping.area[i][0] == 'C')
		{
			colors = cub_handle_colors(mapdata, i);
			if (colors)
			{
				if (mapdata->mapping.area[i][0] == 'F')
					mapdata->mapping.f_color = colors;
				else
					mapdata->mapping.c_color = colors;
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	cub_colors(t_cub3d *mapdata)
{
	if (!check_color_data(mapdata) \
		|| !mapdata->mapping.f_color \
		|| !mapdata->mapping.c_color)
	{
		cub_error("Invalid color data!", mapdata);
		return (0);
	}
	return (1);
}
