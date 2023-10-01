/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:40:03 by matcardo          #+#    #+#             */
/*   Updated: 2023/10/01 02:21:53 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	render_little_line(t_img *img, int x, int y, float angle)
{
	float	x_step;
	float	y_step;
	int		i;

	i = 0;
	x_step = cos(angle) * 5;
	y_step = sin(angle) * 5;
	while (i < 5)
	{
		my_mlx_pixel_put(img, x + x_step * i, y + y_step * i, 0x00FF0000);
		i++;
	}
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

void	render_map_unit(t_img *img, int x, int y)
{
	int i;
	int j;

	i = 1;
	j = 1;
	while (i < 64)
	{
		j = 1;
		while (j < 64)
		{
			my_mlx_pixel_put(img, y * 64 + i, x * 64 + j, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

void	render_map(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < img->map.width)
	{
		j = 0;
		while (j < img->map.height)
		{
			if (img->map.map[i][j] == '1')
				render_map_unit(img, i, j);
			j++;
		}
		i++;
	}
}

void	render_player(t_img *img)
{
	render_little_line(img, img->player.x, img->player.y, img->player.angle);
	render_little_line(img, img->player.x, img->player.y, img->player.angle + PI / 2);
}

float dist_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	raycasterr(t_img *img)
{
	int			i;
	float		atan;
	float		ntan;
	t_raycaster	ray;
	float		distV;
	float		distH;
	float		dist;
	float		hx;
	float		hy;
	float		vx;
	float		vy;

	distV = 10000000000000;
	distH = 10000000000000;
	ray.angle = img->player.angle - DR * 30;
	if (ray.angle < 0)
		ray.angle += 2 * PI;
	if (ray.angle > 2 * PI)
		ray.angle -= 2 * PI;
	i = 0;
	while (i < 60)
	{
		// Horizontal check
		hx = img->player.x;
		hy = img->player.y;
		ray.dof = 0;
		atan = -1 / tan(ray.angle);
		if (ray.angle > PI) // looking up
		{
			ray.first_hit_y = (((int)img->player.y >> BASE_CUBE) \
				<< BASE_CUBE) - 0.0001;
			ray.first_hit_x = (img->player.y - ray.first_hit_y) * atan + img->player.x;
			ray.y_offset = -CUBE_SIZE;
			ray.x_offset = -ray.y_offset * atan;
		}
		else if (ray.angle < PI) // looking down
		{
			ray.first_hit_y = (((int)img->player.y >> BASE_CUBE) \
				<< BASE_CUBE) + CUBE_SIZE;
			ray.first_hit_x = (img->player.y - ray.first_hit_y) * atan + img->player.x;
			ray.y_offset = CUBE_SIZE;
			ray.x_offset = -ray.y_offset * atan;
		}
		else if (ray.angle == 0)
		{
			ray.first_hit_x = img->player.x + 10;
			ray.first_hit_y = img->player.y;
			ray.dof = img->map.height;
		}
		else if (ray.angle == PI)
		{
			ray.first_hit_x = img->player.x - 10;
			ray.first_hit_y = img->player.y;
			ray.dof = img->map.height;
		}

		while (ray.dof < 8)
		{
			ray.map_x = (int)(ray.first_hit_x) >> BASE_CUBE;
			ray.map_y = (int)(ray.first_hit_y) >> BASE_CUBE;
			if (ray.map_x >= 0 && ray.map_y >= 0 && ray.map_x < img->map.width && ray.map_y < img->map.height && img->map.map[ray.map_y][ray.map_x] == '1')
			{
				hx = ray.first_hit_x;
				hy = ray.first_hit_y;
				distH = dist_between_points(img->player.x, img->player.y, hx, hy);
				ray.dof = 8;
			}
			else
			{
				ray.first_hit_x += ray.x_offset;
				ray.first_hit_y += ray.y_offset;
				ray.dof += 1;
				hx = ray.first_hit_x;
				hy = ray.first_hit_y;
				distH = dist_between_points(img->player.x, img->player.y, hx, hy);
			}
		}

		// Vertical check
		vx = img->player.x;
		vy = img->player.y;
		ray.dof = 0;
		ntan = -tan(ray.angle);
		if (ray.angle > PI / 2 && ray.angle < 3 * PI / 2)
		{
			ray.first_hit_x = (((int)img->player.x >> 6) << 6) - 0.0001;
			ray.first_hit_y = (img->player.x - ray.first_hit_x) * ntan + img->player.y;
			ray.x_offset = -64;
			ray.y_offset = -ray.x_offset * ntan;
		}
		else if (ray.angle < PI / 2 || ray.angle > 3 * PI / 2)
		{
			ray.first_hit_x = (((int)img->player.x >> 6) << 6) + 64;
			ray.first_hit_y = (img->player.x - ray.first_hit_x) * ntan + img->player.y;
			ray.x_offset = 64;
			ray.y_offset = -ray.x_offset * ntan;
		}
		else if (ray.angle == PI / 2)
		{
			ray.first_hit_x = img->player.x;
			ray.first_hit_y = img->player.y + 10;
			ray.dof = 8;
		}
		else if (ray.angle == 3 * PI / 2)
		{
			ray.first_hit_x = img->player.x;
			ray.first_hit_y = img->player.y - 10;
			ray.dof = 8;
		}

		while (ray.dof < 8)
		{
			ray.map_x = (int)(ray.first_hit_x) >> 6;
			ray.map_y = (int)(ray.first_hit_y) >> 6;
			if (ray.map_x >= 0 && ray.map_y >= 0 && ray.map_x < img->map.width && ray.map_y < img->map.height && img->map.map[ray.map_y][ray.map_x] == '1')
			{
				vx = ray.first_hit_x;
				vy = ray.first_hit_y;
				distV = dist_between_points(img->player.x, img->player.y, vx, vy);
				ray.dof = 8;
			}
			else
			{
				ray.first_hit_x += ray.x_offset;
				ray.first_hit_y += ray.y_offset;
				ray.dof += 1;
				vx = ray.first_hit_x;
				vy = ray.first_hit_y;
				distV = dist_between_points(img->player.x, img->player.y, vx, vy);
			}
		}

		i++;
		ray.angle += DR;
		if (ray.angle < 0)
			ray.angle += 2 * PI;
		if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		ray.first_hit_x = 0;
		ray.first_hit_y = 0;
		int wall_collor = 0x0000FF00;
		// verticall wall hit
		if (hx > 0 && hy > 0 && hx < img->map.width*64 && hy < img->map.height*64 && distH <= distV)
		{
			ray.first_hit_x = hx;
			ray.first_hit_y = hy;
			dist = distH;
			wall_collor = 0x00FF0000;
		}
		// horizontal wall hit
		if (vx > 0 && vy > 0 && vx < img->map.width*64 && vy < img->map.height*64 && distV < distH)
		{
			ray.first_hit_x = vx;
			ray.first_hit_y = vy;
			dist = distV;
			wall_collor = 0x00550000;
		}
		// printf("i: %d, ray.first_hit_x: %f, ray.first_hit_y: %f\n", i, ray.first_hit_x, ray.first_hit_y);
		render_line(img, img->player.x, img->player.y, ray.first_hit_x, ray.first_hit_y, 0x00FF0000);
		//draw walls
		
		// fix fish eye
		float ca = img->player.angle - ray.angle;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		dist = dist * cos(ca);
		// line height
		float lineH = (64 * 320) / dist;
		if (lineH > 320)
			lineH = 320;
		// line offset
		int lineO = 160 - lineH / 2;
		if (lineO < 0)
			lineO = 0;
		int j = 0;
		while (j < 8)
		{
			render_line(img, 512 + i*8 + j, 100+lineO , 512 + i*8 + j, 100 + lineH+lineO, wall_collor);
			j++;
		}
		
	}
}

// Main functions

void	print_screen(t_img *img)
{
	raycasterr(img);
	// render_player(img);
	// render_map(img);
}

void	start_image(t_win *win)
{
	win->img.img_ptr = mlx_new_image(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	win->img.addr = mlx_get_data_addr(win->img.img_ptr, &win->img.bpp, \
	&win->img.line_len, &win->img.endian);
	print_screen(&(win->img));
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img_ptr, 0, 0);
	mlx_destroy_image(win->mlx_ptr, win->img.img_ptr);
}

int	start_window(t_win *win)
{
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
		return (MLX_ERROR);
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (win->win_ptr == NULL)
	{
		free(win->mlx_ptr);
		return (MLX_ERROR);
	}
	start_image(win);
	// mlx_mouse_hook(win->win_ptr, zoom, win);
	mlx_hook(win->win_ptr, 2, 1L << 0, &handle_input, win);
	mlx_hook(win->win_ptr, 17, 1L << 0, &close_window, win);
	// mlx_expose_hook(win->win_ptr, (void *)start_image, win);
	mlx_loop(win->mlx_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (1);
	if (init_game(argv[1]))
		return (1);
	return (0);
}

// Init functions

int	init_game(char *file)
{
	t_win	win;

	init_game_params(&win, file);
	if (!start_window(&win))
		return (1);
	return (0);
}

void	init_game_params(t_win *win, char *file)
{
	win->mlx_ptr = NULL;
	init_map_dimensions(win, file);
	init_map(win, file);
	init_player_position(win, file);
}

void	init_player_position(t_win *win, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (is_map(line))
		{
			init_player_position_line(win, line, i);
			i++;
			free(line);
		}
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_player_position_line(t_win *win, char *line, int i)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S' || \
			line[j] == 'E' || line[j] == 'W')
		{
			win->img.player.x = j * CUBE_SIZE + CUBE_SIZE / 2;
			win->img.player.y = i * CUBE_SIZE + CUBE_SIZE / 2;
			if (line[j] == 'N')
				win->img.player.angle = 3 * PI / 2;
			else if (line[j] == 'S')
				win->img.player.angle = PI / 2;
			else if (line[j] == 'E')
				win->img.player.angle = 0;
			else if (line[j] == 'W')
				win->img.player.angle = PI;
			win->img.player.cos = cos(win->img.player.angle) * 5;
			win->img.player.sin = sin(win->img.player.angle) * 5;
		}
		j++;
	}
}

void	init_map(t_win *win, char *file)
{
	int		fd;
	char	*line;
	int		i;

	win->img.map.map = malloc(sizeof(char *) * win->img.map.width);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (is_map(line))
		{
			win->img.map.map[i] = ft_strdup(line);
			i++;
			free(line);
		}
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_map_dimensions(t_win *win, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	win->img.map.height = 0;
	win->img.map.width = 3;
	while (line)
	{
		if (is_map(line))
		{
			win->img.map.height++;
			if (win->img.map.width < (int)ft_strlen(line) - 1)
				win->img.map.width = ft_strlen(line) - 1;
			free(line);
		}
		line = get_next_line(fd);
	}
	close(fd);
}

short int	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '1'))
	{
		if (line[i] == '1')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
