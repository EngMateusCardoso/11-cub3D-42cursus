/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen_temp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:24 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 15:28:27 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	print_screen(t_img *img)
{
	print_screen_background(img);
	raycasterr(img);
	// render_map(img);
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

float	fix_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	raycasterr(t_img *img)
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

t_ray fix_fish_eye(t_ray ray, float angle)
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

t_coord	get_horizontal_hit(t_img *img, float angle)
{
	t_raycaster	ray;
	t_coord		hit;
	int			i;

	i = 0;
	hit.len = 10000000000000;
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
		hit.len = dist_between_points(img->player.x, img->player.y, hit.x, hit.y);
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
	else if (angle < PI)
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

t_coord	get_vertical_hit(t_img *img, float angle)
{
	t_raycaster	ray;
	t_coord		hit;
	int			i;

	i = 0;
	hit.len = 10000000000000;
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
	else if (angle < PI / 2 || angle > 3 * PI / 2)
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

float	dist_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

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
	int i;
	int j;

	i = 1;
	j = 1;
	while (i < CUBE_SIZE)
	{
		j = 1;
		while (j < CUBE_SIZE)
		{
			my_mlx_pixel_put(img, (y * CUBE_SIZE + i)*img->map.minimap_scale, (x * CUBE_SIZE + j)*img->map.minimap_scale, color);
			j++;
		}
		i++;
	}
}

void	render_player(t_img *img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < PLAYER_SIZE * 2)
	{
		j = 0;
		while (j < PLAYER_SIZE * 2)
		{
			my_mlx_pixel_put(img, ((img->player.x/CUBE_SIZE) * CUBE_SIZE + j - PLAYER_SIZE)*img->map.minimap_scale, ((img->player.y/CUBE_SIZE) * CUBE_SIZE + i - PLAYER_SIZE)*img->map.minimap_scale, PLAYER_MINIMAP_COLOR);
			j++;
		}
		i++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}
