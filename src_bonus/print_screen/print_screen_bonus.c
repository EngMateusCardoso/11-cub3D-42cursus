/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:48:54 by matcardo          #+#    #+#             */
/*   Updated: 2024/01/04 03:58:00 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3D_bonus.h"

void	ponto(float x, float y, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			my_mlx_pixel_put(img, x + i, y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void   render_sprites(t_img *img, int sprite_i)
{
	float	sprite_x;
	float	sprite_y;
	float	sprite_z;
	float	sprite_a;
	float	sprite_b;
	float	sprite_dist;
	int		color;
	int		sprite_nvl;

	sprite_dist = dist_between_points(img->player.x, img->player.y, img->sprite.x[sprite_i], img->sprite.y[sprite_i]);
	if (sprite_dist > 500)
		sprite_nvl = S1;
	else if (sprite_dist > 250)
		sprite_nvl = S2;
	else
		sprite_nvl = S3;
	sprite_x = (img->sprite.x[sprite_i] - img->player.x);
	sprite_y = (img->sprite.y[sprite_i] - img->player.y);
	sprite_a = sprite_x * img->player.cos + sprite_y * img->player.sin;
	sprite_b = -sprite_x * img->player.sin + sprite_y * img->player.cos;
	sprite_z = 128;
	sprite_y = sprite_a;
	sprite_x = sprite_b;
	//convert sprite coordinates to screen space
	sprite_x = ((sprite_x * 1150) / sprite_y) + WIN_WIDTH / 2;
	sprite_y = ((sprite_z * 1150) / sprite_y) + WIN_HEIGHT / 2;

	int x, y;
	int scale = 32 * 1280 / sprite_dist;
	x = (int)sprite_x - scale / 2;
	while (x < (int)sprite_x + scale / 2)
	{
		y = 0;
		while (y < scale)
		{
			if (x > 0 && x < WIN_WIDTH && \
			sprite_y + y > 0 && sprite_y + y < WIN_HEIGHT && \
			sprite_a >= 0 && \
			sprite_dist < img->sprite.depth[x / 2])
			{
				color = img->textures[sprite_nvl][((int)(x - sprite_x + scale / 2)) * \
				img->texture_width[sprite_nvl] / scale][((int)(y * 1280 / scale)) * \
				img->texture_width[sprite_nvl] / 1280];
				if (color != -16777216)
					my_mlx_pixel_put(img, x, sprite_y + y, color);
			}
			y++;
		}
		x++;
	}
}

void	print_screen(t_img *img)
{
	int	count_sprites;

	print_screen_background(img);
	raycaster(img);
	count_sprites = 0;
	while (count_sprites < img->sprite.count_sprites)
	{
		render_sprites(img, count_sprites);
		count_sprites++;
	}
	render_map(img);
}

void	print_screen_background(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			if (j < WIN_HEIGHT / 2)
				my_mlx_pixel_put(img, i, j, img->ceiling_color);
			else
				my_mlx_pixel_put(img, i, j, img->floor_color);
			j++;
		}
		i++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
