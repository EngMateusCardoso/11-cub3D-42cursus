/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_hit_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:52:16 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/17 20:14:39 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3D_bonus.h"

t_coord	get_vertical_hit(t_img *img, float angle)
{
	t_raycaster	ray;
	t_coord		hit;
	int			i;

	i = 0;
	hit.len = 10000000000000.0;
	hit.x = img->player.x;
	hit.y = img->player.y;
	ray = get_vertical_hit_ray(img, angle);
	if (angle == PI / 2 || angle == 3 * PI / 2)
		i = img->map.width;
	while (i < img->map.width)
	{
		vertical_hit_ray_update(img, &ray, &i);
		hit.x = ray.first_hit_x;
		hit.y = ray.first_hit_y;
		hit.len = dist_between_points(img->player.x, img->player.y, \
			hit.x, hit.y);
	}
	return (hit);
}

t_raycaster	get_vertical_hit_ray(t_img *img, float angle)
{
	t_raycaster	ray;

	if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		ray.first_hit_x = (((int)img->player.x >> BASE_CUBE) << \
			BASE_CUBE) - 0.001;
		ray.first_hit_y = (img->player.x - ray.first_hit_x) * \
			-tan(angle) + img->player.y;
		ray.x_offset = -CUBE_SIZE;
		ray.y_offset = -ray.x_offset * -tan(angle);
	}
	if (angle < PI / 2 || angle > 3 * PI / 2)
	{
		ray.first_hit_x = (((int)img->player.x >> BASE_CUBE) \
			<< BASE_CUBE) + CUBE_SIZE;
		ray.first_hit_y = (img->player.x - ray.first_hit_x) * \
			-tan(angle) + img->player.y;
		ray.x_offset = CUBE_SIZE;
		ray.y_offset = -ray.x_offset * -tan(angle);
	}
	return (ray);
}

void	vertical_hit_ray_update(t_img *img, t_raycaster *ray, int *i)
{
	(*ray).map_x = (int)((*ray).first_hit_x) >> BASE_CUBE;
	(*ray).map_y = (int)((*ray).first_hit_y) >> BASE_CUBE;
	if ((*ray).map_x >= 0 && (*ray).map_y >= 0 \
		&& (*ray).map_x < img->map.width && (*ray).map_y < img->map.height && \
		img->map.map[(*ray).map_y][(*ray).map_x] == '1')
		*i = img->map.width;
	else
	{
		(*ray).first_hit_x += (*ray).x_offset;
		(*ray).first_hit_y += (*ray).y_offset;
		*i += 1;
	}
}
