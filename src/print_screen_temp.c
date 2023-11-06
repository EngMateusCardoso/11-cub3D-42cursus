/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen_temp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:24 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/06 00:46:10 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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

void	print_screen(t_img *img)
{
	// printf("print_screen\n");
	print_screen_background(img);
	// printf("print_screen_background\n");
	raycasterr(img);
	// printf("raycasterr\n");
	render_map(img);
	// printf("render_map\n");
}

void	raycasterr(t_img *img)
{
	t_coord	vert_hit;
	t_coord	hor_hit;
	float	angle;
	float	dist;
	float	x_hit;
	int		i;

	angle = img->player.angle - DR * (ANGLE_OF_VIEW / 2);
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	i = 0;
	while (i < RAYCASTER_NUM_RAYS)
	{
		hor_hit = get_horizontal_hit(img, angle);
		vert_hit = get_vertical_hit(img, angle);
		angle += ((float)ANGLE_OF_VIEW / RAYCASTER_NUM_RAYS) * DR;
		if (angle < 0)
			angle += 2 * PI;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		int wall_direction = NO;
		// verticall wall hit
		if (hor_hit.x > 0 && hor_hit.y > 0 && hor_hit.x < img->map.width*CUBE_SIZE && hor_hit.y < img->map.height * CUBE_SIZE && hor_hit.len <= vert_hit.len)
		{
			dist = hor_hit.len;
			x_hit = hor_hit.x;
			if (angle > 0 && angle < PI)
				wall_direction = SO;
			else
				wall_direction = NO;
		// render_line(img, img->player.x, img->player.y, hor_hit.x, hor_hit.y, 0x00FF0000);
		}
		// horizontal wall hit
		if (vert_hit.x > 0 && vert_hit.y > 0 && vert_hit.x < img->map.width*CUBE_SIZE && vert_hit.y < img->map.height*CUBE_SIZE && vert_hit.len < hor_hit.len)
		{
			dist = vert_hit.len;
			x_hit = vert_hit.y;
			if (angle > PI / 2 && angle < 3 * PI / 2)
				wall_direction = WE;
			else
				wall_direction = EA;
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
		// passo da textura
		float step = img->texture_height[wall_direction]  / lineH;
		// quanbdo esta próximo começa a textura do offset
		float step_offset = 0.0;
		if (lineH > WIN_HEIGHT)
		{
			step_offset = ((lineH - WIN_HEIGHT) / 2.0);
			lineH = WIN_HEIGHT;
		}


		// line offset
		int lineO = WIN_HEIGHT / 2 - lineH / 2;
		if (lineO < 0)
			lineO = 0;

		int j = 0;
		// Laço para criar espessura da linha vertical
		while (j <= WIN_WIDTH / RAYCASTER_NUM_RAYS)
		{
			render_line(img, i * WIN_WIDTH / RAYCASTER_NUM_RAYS + j, 1 + lineO, i * WIN_WIDTH / RAYCASTER_NUM_RAYS + j, 1 + lineH + lineO, wall_direction, step, step_offset, x_hit);
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
	// if (direction == NO)
	// 	color = img->textures[NO][0];
	// else if (direction == SO)
	// 	color = img->textures[SO][0];
	// else if (direction == WE)
	// 	color = img->textures[WE][0];
	// else if (direction == EA)
	// 	color = img->textures[EA][0];
	while (x0_int <= x1_int)
	{
		i = 1 + step_offset * step;
		while (y0_int <= y1_int)
		{
			color = img->textures[direction][0][(int)(i)];
			color = img->textures[direction][((int)x_hit % CUBE_SIZE) * img->texture_width[direction]/CUBE_SIZE][(int)(i)];
			// printf("x0_int: %d, y0_int: %d, x1_int: %d, y1_int: %d\n", x0_int, y0_int, x1_int, y1_int);
			// printf("x0_int %% 64: %d, y0_int %% 64: %d\n", x0_int % 64 * 64, y0_int % 64 * 64);
			// printf("i: %d, length: %d\n", i, length);
			// my_mlx_pixel_put(img, x0_int, y0_int, color[y0_int % 64 * 64]);
			my_mlx_pixel_put(img, x0_int, y0_int, color);
			i += step;
			y0_int++;
		}
		x0_int++; 
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