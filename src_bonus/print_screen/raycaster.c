/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:50:03 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 16:25:19 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3D.h"

void	raycaster(t_img *img)
{
	t_coord	vert_hit;
	t_coord	hor_hit;
	t_ray	ray;
	int		i;

	ray.angle = img->player.angle - DR * (ANGLE_OF_VIEW / 2);
	ray.angle = fix_angle(ray.angle);
	i = 0;
	while (i < RAYCASTER_NUM_RAYS)
	{
		hor_hit = get_horizontal_hit(img, ray.angle);
		vert_hit = get_vertical_hit(img, ray.angle);
		ray.angle += ((float)ANGLE_OF_VIEW / RAYCASTER_NUM_RAYS) * DR;
		ray.angle = fix_angle(ray.angle);
		ray = get_ray(img, hor_hit, vert_hit, ray);
		ray = fix_fish_eye(ray, img->player.angle);
		draw_walls(img, ray, i);
		i++;
	}
}

float	fix_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

t_ray	get_ray(t_img *img, t_coord hor_hit, t_coord vert_hit, t_ray ray)
{
	if (hor_hit.x > 0 && hor_hit.y > 0 && \
		hor_hit.x < img->map.width * CUBE_SIZE && \
		hor_hit.y < img->map.height * CUBE_SIZE && hor_hit.len <= vert_hit.len)
	{
		ray.dist = hor_hit.len;
		ray.x_hit = hor_hit.x;
		if (ray.angle > 0 && ray.angle < PI)
			ray.wall_direction = SO;
		else
			ray.wall_direction = NO;
	}
	if (vert_hit.x > 0 && vert_hit.y > 0 && \
		vert_hit.x < img->map.width * CUBE_SIZE && \
		vert_hit.y < img->map.height * CUBE_SIZE && vert_hit.len < hor_hit.len)
	{
		ray.dist = vert_hit.len;
		ray.x_hit = vert_hit.y;
		if (ray.angle > PI / 2 && ray.angle < 3 * PI / 2)
			ray.wall_direction = WE;
		else
			ray.wall_direction = EA;
	}
	return (ray);
}

t_ray	fix_fish_eye(t_ray ray, float angle)
{
	float	ca;

	ca = angle - ray.angle;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	ray.dist = ray.dist * cos(ca);
	return (ray);
}
