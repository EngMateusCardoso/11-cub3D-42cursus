/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:53:46 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 15:54:15 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"


void	draw_walls(t_img *img, t_ray ray, int ray_index)
{
	t_wall_vert_pxl	wall_params;

	wall_params.line_height = (CUBE_SIZE * WIN_HEIGHT) / ray.dist;
	wall_params.step = \
		img->texture_height[ray.wall_direction] / wall_params.line_height;
	wall_params.step_offset = 0.0;
	if (wall_params.line_height > WIN_HEIGHT)
	{
		wall_params.step_offset = \
			((wall_params.line_height - WIN_HEIGHT) / 2.0);
		wall_params.line_height = WIN_HEIGHT;
	}
	wall_params.line_offset = WIN_HEIGHT / 2 - wall_params.line_height / 2;
	if (wall_params.line_offset < 0)
		wall_params.line_offset = 0;
	wall_params.ray_pixel = 0;
	while (wall_params.ray_pixel <= WIN_WIDTH / RAYCASTER_NUM_RAYS)
	{
		draw_wall_column(img, ray, wall_params, ray_index);
		wall_params.ray_pixel++;
	}
}

void	draw_wall_column(t_img *img, t_ray ray, \
	t_wall_vert_pxl wall_params, int ray_i)
{
	int		x;
	int		y0;
	int		y1;
	float	iv;
	int		color;

	x = (int)(ray_i * WIN_WIDTH / RAYCASTER_NUM_RAYS + wall_params.ray_pixel);
	y0 = (int)(1 + wall_params.line_offset);
	y1 = (int)(1 + wall_params.line_height + wall_params.line_offset);
	iv = 1 + wall_params.step_offset * wall_params.step;
	while (y0 <= y1)
	{
		if (ray.wall_direction == NO || ray.wall_direction == EA)
			color = img->textures[ray.wall_direction][((int)ray.x_hit % \
			CUBE_SIZE) * img->texture_width[ray.wall_direction] / \
			CUBE_SIZE][(int)(iv)];
		else if (ray.wall_direction == SO || ray.wall_direction == WE)
			color = img->textures[ray.wall_direction][((CUBE_SIZE - 1) - \
				((int)ray.x_hit % CUBE_SIZE)) * \
				img->texture_width[ray.wall_direction] / \
				CUBE_SIZE][(int)(iv)];
		my_mlx_pixel_put(img, (int)x, y0, color);
		iv += wall_params.step;
		y0++;
	}
}
