/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:24 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 20:11:37 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3D.h"

void	render_map(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < img->map.height)
	{
		j = 0;
		while (img->map.map[i][j] != '\0' && img->map.map[i][j] != '\n')
		{
			if (img->map.map[i][j] == '1')
				render_map_unit(img, i, j, WALL_MINIMAP_COLOR);
			j++;
		}
		i++;
	}
	render_player(img);
}

void	render_map_unit(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (i < CUBE_SIZE)
	{
		j = 1;
		while (j < CUBE_SIZE)
		{
			my_mlx_pixel_put(img, (y * CUBE_SIZE + i) * img->map.minimap_scale \
				, (x * CUBE_SIZE + j) * img->map.minimap_scale, color);
			j++;
		}
		i++;
	}
}

void	render_player(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < PLAYER_SIZE * 2)
	{
		j = 0;
		while (j < PLAYER_SIZE * 2)
		{
			my_mlx_pixel_put(img, ((img->player.x / CUBE_SIZE) * CUBE_SIZE \
				+ j - PLAYER_SIZE) * img->map.minimap_scale, \
				((img->player.y / CUBE_SIZE) * CUBE_SIZE + i - PLAYER_SIZE) * \
				img->map.minimap_scale, PLAYER_MINIMAP_COLOR);
			j++;
		}
		i++;
	}
}
