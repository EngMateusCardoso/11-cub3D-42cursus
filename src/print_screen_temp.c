/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen_temp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:24 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 13:07:59 by matcardo         ###   ########.fr       */
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

void	draw_walls(t_img *img, t_ray ray, int i)
{
	float	line_height;
	float	line_offset;
	int		j;
	float	step;
	float	step_offset;

	line_height = (CUBE_SIZE * WIN_HEIGHT) / ray.dist;
	step = img->texture_height[ray.wall_direction] / line_height;
	step_offset = 0.0;
	if (line_height > WIN_HEIGHT)
	{
		step_offset = ((line_height - WIN_HEIGHT) / 2.0);
		line_height = WIN_HEIGHT;
	}
	line_offset = WIN_HEIGHT / 2 - line_height / 2;
	if (line_offset < 0)
		line_offset = 0;
	j = 0;
	while (j <= WIN_WIDTH / RAYCASTER_NUM_RAYS)
	{
		render_line(img, i * WIN_WIDTH / RAYCASTER_NUM_RAYS + j, 1 + line_offset, i * WIN_WIDTH / RAYCASTER_NUM_RAYS + j, 1 + line_height + line_offset, ray.wall_direction, step, step_offset, ray.x_hit);
		// color = img->textures[ray.wall_direction][0][(int)(j * img->texture_height[ray.wall_direction] / line_height)];
		// if (ray.wall_direction == NO || ray.wall_direction == EA)
		// 	color = img->textures[ray.wall_direction][((int)ray.x_hit % CUBE_SIZE) * img->texture_width[ray.wall_direction]/CUBE_SIZE][(int)(j * img->texture_height[ray.wall_direction] / line_height)];
		// else if (ray.wall_direction == SO || ray.wall_direction == WE)
		// 	color = img->textures[ray.wall_direction][((CUBE_SIZE - 1) - ((int)ray.x_hit % CUBE_SIZE))* img->texture_width[ray.wall_direction]/CUBE_SIZE][(int)(j * img->texture_height[ray.wall_direction] / line_height)];
		// my_mlx_pixel_put(img, i * WIN_WIDTH / RAYCASTER_NUM_RAYS + j, 1 + line_offset, color);
		j++;
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
	if (angle > PI) // looking up
	{
		ray.first_hit_y = (((int)img->player.y >> BASE_CUBE) \
			<< BASE_CUBE) - 0.001;
		ray.first_hit_x = (img->player.y - ray.first_hit_y) * -1 / tan(angle) + img->player.x;
		ray.y_offset = -CUBE_SIZE;
		ray.x_offset = -ray.y_offset * -1 / tan(angle);
	}
	else if (angle < PI) // looking down
	{
		ray.first_hit_y = (((int)img->player.y >> BASE_CUBE) \
			<< BASE_CUBE) + CUBE_SIZE;
		ray.first_hit_x = (img->player.y - ray.first_hit_y) * -1 / tan(angle) + img->player.x;
		ray.y_offset = CUBE_SIZE;
		ray.x_offset = -ray.y_offset * -1 / tan(angle);
	}
	else if (angle == 0)
		i = img->map.height;
	else if (angle == PI)
		i = img->map.height;

	while (i < img->map.height)
	{
		ray.map_x = (int)(ray.first_hit_x) >> BASE_CUBE;
		ray.map_y = (int)(ray.first_hit_y) >> BASE_CUBE;
		if (ray.map_x >= 0 && ray.map_y >= 0 && ray.map_x < img->map.width && ray.map_y < img->map.height && img->map.map[ray.map_y][ray.map_x] == '1')
			i = img->map.height;
		else
		{
			ray.first_hit_x += ray.x_offset;
			ray.first_hit_y += ray.y_offset;
			i += 1;
		}
		hit.x = ray.first_hit_x;
		hit.y = ray.first_hit_y;
		hit.len = dist_between_points(img->player.x, img->player.y, hit.x, hit.y);
	}
	return (hit);
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
	if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		ray.first_hit_x = (((int)img->player.x >> BASE_CUBE) << BASE_CUBE) - 0.001;
		ray.first_hit_y = (img->player.x - ray.first_hit_x) * -tan(angle) + img->player.y;
		ray.x_offset = -CUBE_SIZE;
		ray.y_offset = -ray.x_offset * -tan(angle);
	}
	else if (angle < PI / 2 || angle > 3 * PI / 2)
	{
		ray.first_hit_x = (((int)img->player.x >> BASE_CUBE) << BASE_CUBE) + CUBE_SIZE;
		ray.first_hit_y = (img->player.x - ray.first_hit_x) * -tan(angle) + img->player.y;
		ray.x_offset = CUBE_SIZE;
		ray.y_offset = -ray.x_offset * -tan(angle);
	}
	else if (angle == PI / 2)
		i = img->map.width;
	else if (angle == 3 * PI / 2)
		i = img->map.width;

	while (i < img->map.width)
	{
		ray.map_x = (int)(ray.first_hit_x) >> BASE_CUBE;
		ray.map_y = (int)(ray.first_hit_y) >> BASE_CUBE;
		if (ray.map_x >= 0 && ray.map_y >= 0 && ray.map_x < img->map.width && ray.map_y < img->map.height && img->map.map[ray.map_y][ray.map_x] == '1')
			i = img->map.width;
		else
		{
			ray.first_hit_x += ray.x_offset;
			ray.first_hit_y += ray.y_offset;
			i += 1;
		}
			hit.x = ray.first_hit_x;
			hit.y = ray.first_hit_y;
			hit.len = dist_between_points(img->player.x, img->player.y, hit.x, hit.y);
	}
	return (hit);
}

void	render_line(t_img *img, float x0, float y0, float x1, float y1, int direction, float step, float step_offset, float x_hit)
{
	int x0_int;
	int x1_int;
	int y0_int;
	int y1_int;
	float i;
	int	color;

	if (x0 < x1) {
		x0_int = round(x0);
		x1_int = round(x1);
	}
	else {
		x1_int = round(x0);
		x0_int = round(x1);
	}
	if (y0 < y1) {
		y0_int = round(y0);
		y1_int = round(y1);
	}
	else {
		y1_int = round(y0);
		y0_int = round(y1);
	}
	while (x0_int <= x1_int)
	{
		i = 1 + step_offset * step;
		while (y0_int <= y1_int)
		{
			color = img->textures[direction][0][(int)(i)];
			if (direction == NO || direction == EA)
				color = img->textures[direction][((int)x_hit % CUBE_SIZE) * img->texture_width[direction]/CUBE_SIZE][(int)(i)];
			else if (direction == SO || direction == WE)
				color = img->textures[direction][((CUBE_SIZE - 1) - ((int)x_hit % CUBE_SIZE))* img->texture_width[direction]/CUBE_SIZE][(int)(i)];
			my_mlx_pixel_put(img, x0_int, y0_int, color);
			i += step;
			y0_int++;
		}
		x0_int++; 
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
