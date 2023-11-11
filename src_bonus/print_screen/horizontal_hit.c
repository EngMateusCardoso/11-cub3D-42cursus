/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:52:19 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 20:14:13 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3D.h"

t_coord	get_horizontal_hit(t_img *img, float angle)
{
	t_raycaster	ray;
	t_coord		hit;
	int			i;

	i = 0;
	hit.len = 10000000000000.0;
	hit.x = img->player.x;
	hit.y = img->player.y;
	ray = get_horizontal_hit_ray(img, angle);
	if (angle == 0 || angle == PI)
		i = img->map.height;
	while (i < img->map.height)
	{
		horizontal_hit_ray_update(img, &ray, &i);
		hit.x = ray.first_hit_x;
		hit.y = ray.first_hit_y;
		hit.len = dist_between_points(img->player.x, img->player.y, \
			hit.x, hit.y);
	}
	return (hit);
}

t_raycaster	get_horizontal_hit_ray(t_img *img, float angle)
{
	t_raycaster	ray;

	if (angle > PI)
	{
		ray.first_hit_y = (((int)img->player.y >> BASE_CUBE) \
			<< BASE_CUBE) - 0.001;
		ray.first_hit_x = (img->player.y - ray.first_hit_y) * \
			-1 / tan(angle) + img->player.x;
		ray.y_offset = -CUBE_SIZE;
		ray.x_offset = -ray.y_offset * -1 / tan(angle);
	}
	if (angle < PI)
	{
		ray.first_hit_y = (((int)img->player.y >> BASE_CUBE) \
			<< BASE_CUBE) + CUBE_SIZE;
		ray.first_hit_x = (img->player.y - ray.first_hit_y) * \
			-1 / tan(angle) + img->player.x;
		ray.y_offset = CUBE_SIZE;
		ray.x_offset = -ray.y_offset * -1 / tan(angle);
	}
	return (ray);
}

void	horizontal_hit_ray_update(t_img *img, t_raycaster *ray, int *i)
{
	(*ray).map_x = (int)((*ray).first_hit_x) >> BASE_CUBE;
	(*ray).map_y = (int)((*ray).first_hit_y) >> BASE_CUBE;
	if ((*ray).map_x >= 0 && (*ray).map_y >= 0 \
		&& (*ray).map_x < img->map.width && (*ray).map_y < img->map.height && \
		img->map.map[(*ray).map_y][(*ray).map_x] == '1')
		*i = img->map.height;
	else
	{
		(*ray).first_hit_x += (*ray).x_offset;
		(*ray).first_hit_y += (*ray).y_offset;
		*i += 1;
	}
}

float	dist_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
