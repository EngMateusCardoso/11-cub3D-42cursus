/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen_temp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:24 by matcardo          #+#    #+#             */
/*   Updated: 2023/10/14 15:27:07 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	print_screen(t_img *img)
{
	raycasterr(img);
	// render_player(img);
	// render_map(img);
}


void	raycasterr(t_img *img)
{
	t_coord	vert_hit;
	t_coord	hor_hit;
	float	angle;
	float	dist;
	int		i;

	angle = img->player.angle - DR * 30;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	i = 0;
	while (i < 60)
	{
		hor_hit = get_horizontal_hit(img, angle);
		vert_hit = get_vertical_hit(img, angle);
		angle += DR;
		if (angle < 0)
			angle += 2 * PI;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		int wall_collor = 0x0000FF00;
		// verticall wall hit
		if (hor_hit.x > 0 && hor_hit.y > 0 && hor_hit.x < img->map.width*64 && hor_hit.y < img->map.height * 64 && hor_hit.len <= vert_hit.len)
		{
			dist = hor_hit.len;
			wall_collor = 0x00FF0000;
		// render_line(img, img->player.x, img->player.y, hor_hit.x, hor_hit.y, 0x00FF0000);
		}
		// horizontal wall hit
		if (vert_hit.x > 0 && vert_hit.y > 0 && vert_hit.x < img->map.width*64 && vert_hit.y < img->map.height*64 && vert_hit.len < hor_hit.len)
		{
			dist = vert_hit.len;
			wall_collor = 0x00550000;
		// render_line(img, img->player.x, img->player.y, vert_hit.x, vert_hit.y, 0x00FF0000);
		}
		//draw walls
		// fix fish eye
		float ca = img->player.angle - angle;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		dist = dist * cos(ca);
		// line height
		float lineH = (CUBE_SIZE * WIN_HEIGHT) / dist;
		if (lineH > WIN_HEIGHT)
			lineH = WIN_HEIGHT;
		// line offset
		int lineO = WIN_HEIGHT / 2 - lineH / 2;
		if (lineO < 0)
			lineO = 0;
		int j = 0;
		while (j < WIN_WIDTH / 60)
		{
			render_line(img, i * WIN_WIDTH / 60 + j, 1 + lineO, i * WIN_WIDTH / 60 + j, 1 + lineH + lineO, wall_collor);
			j++;
		}
		i++;
	}
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
			<< BASE_CUBE) - 0.0001;
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
		ray.first_hit_x = (((int)img->player.x >> BASE_CUBE) << BASE_CUBE) - 0.0001;
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

void	render_line(t_img *img, float x0, float y0, float x1, float y1, int color)
{
	float	x_step;
	float	y_step;
	int		i;

	i = 0;
	x_step = (x1 - x0) / 64;
	y_step = (y1 - y0) / 64;
	while (i < 64)
	{
		my_mlx_pixel_put(img, x0 + x_step * i, y0 + y_step * i, color);
		i++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

float	dist_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

// void	render_player(t_img *img)
// { 
// 	render_little_line(img, img->player.x, img->player.y, img->player.angle);
// 	render_little_line(img, img->player.x, img->player.y, img->player.angle + PI / 2);
// }

// void	render_little_line(t_img *img, int x, int y, float angle)
// {
// 	float	x_step;
// 	float	y_step;
// 	int		i;

// 	i = 0;
// 	x_step = cos(angle) * 5;
// 	y_step = sin(angle) * 5;
// 	while (i < 5)
// 	{
// 		my_mlx_pixel_put(img, x + x_step * i, y + y_step * i, 0x00FF0000);
// 		i++;
// 	}
// }

// void	render_map(t_img *img)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (i < img->map.width)
// 	{
// 		j = 0;
// 		while (j < img->map.height)
// 		{
// 			if (img->map.map[i][j] == '1')
// 				render_map_unit(img, i, j);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	render_map_unit(t_img *img, int x, int y)
// {
// 	int i;
// 	int j;

// 	i = 1;
// 	j = 1;
// 	while (i < 64)
// 	{
// 		j = 1;
// 		while (j < 64)
// 		{
// 			my_mlx_pixel_put(img, y * 64 + i, x * 64 + j, 0x00FFFFFF);
// 			j++;
// 		}
// 		i++;
// 	}
// }