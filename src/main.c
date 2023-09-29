/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:40:03 by matcardo          #+#    #+#             */
/*   Updated: 2023/09/29 16:16:03 by matcardo         ###   ########.fr       */
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
			if (img->map.map[i][j] == 1)
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
	ray.ra = img->player.angle - DR * 30;
	if (ray.ra < 0)
		ray.ra += 2 * PI;
	if (ray.ra > 2 * PI)
		ray.ra -= 2 * PI;
	i = 0;
	while (i < 60)
	{
		hx = img->player.x;
		hy = img->player.y;
		ray.dof = 0;
		atan = -1 / tan(ray.ra);
		if (ray.ra > PI)
		{
			ray.ry = (((int)img->player.y >> 6) << 6) - 0.0001;
			ray.rx = (img->player.y - ray.ry) * atan + img->player.x;
			ray.yo = -64;
			ray.xo = -ray.yo * atan;
		}
		else if (ray.ra < PI)
		{
			ray.ry = (((int)img->player.y >> 6) << 6) + 64;
			ray.rx = (img->player.y - ray.ry) * atan + img->player.x;
			ray.yo = 64;
			ray.xo = -ray.yo * atan;
		}
		else if (ray.ra == 0)
		{
			ray.rx = img->player.x + 10;
			ray.ry = img->player.y;
			ray.dof = 8;
		}
		else if (ray.ra == PI)
		{
			ray.rx = img->player.x - 10;
			ray.ry = img->player.y;
			ray.dof = 8;
		}
		while (ray.dof < 8)
		{
			ray.mx = (int)(ray.rx) >> 6;
			ray.my = (int)(ray.ry) >> 6;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < img->map.width && ray.my < img->map.height && img->map.map[ray.my][ray.mx] == 1)
			{
				hx = ray.rx;
				hy = ray.ry;
				distH = dist_between_points(img->player.x, img->player.y, hx, hy);
				ray.dof = 8;
			}
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
				hx = ray.rx;
				hy = ray.ry;
				distH = dist_between_points(img->player.x, img->player.y, hx, hy);
			}
		}


		vx = img->player.x;
		vy = img->player.y;
		ray.dof = 0;
		ntan = -tan(ray.ra);
		if (ray.ra > PI / 2 && ray.ra < 3 * PI / 2)
		{
			ray.rx = (((int)img->player.x >> 6) << 6) - 0.0001;
			ray.ry = (img->player.x - ray.rx) * ntan + img->player.y;
			ray.xo = -64;
			ray.yo = -ray.xo * ntan;
		}
		else if (ray.ra < PI / 2 || ray.ra > 3 * PI / 2)
		{
			ray.rx = (((int)img->player.x >> 6) << 6) + 64;
			ray.ry = (img->player.x - ray.rx) * ntan + img->player.y;
			ray.xo = 64;
			ray.yo = -ray.xo * ntan;
		}
		else if (ray.ra == PI / 2)
		{
			ray.rx = img->player.x;
			ray.ry = img->player.y + 10;
			ray.dof = 8;
		}
		else if (ray.ra == 3 * PI / 2)
		{
			ray.rx = img->player.x;
			ray.ry = img->player.y - 10;
			ray.dof = 8;
		}
		while (ray.dof < 8)
		{
			ray.mx = (int)(ray.rx) >> 6;
			ray.my = (int)(ray.ry) >> 6;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < img->map.width && ray.my < img->map.height && img->map.map[ray.my][ray.mx] == 1)
			{
				vx = ray.rx;
				vy = ray.ry;
				distV = dist_between_points(img->player.x, img->player.y, vx, vy);
				ray.dof = 8;
			}
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
				vx = ray.rx;
				vy = ray.ry;
				distV = dist_between_points(img->player.x, img->player.y, vx, vy);
			}
		}

		i++;
		ray.ra += DR;
		if (ray.ra < 0)
			ray.ra += 2 * PI;
		if (ray.ra > 2 * PI)
			ray.ra -= 2 * PI;
		ray.rx = 0;
		ray.ry = 0;
		int wall_collor = 0x0000FF00;
		// verticall wall hit
		if (hx > 0 && hy > 0 && hx < img->map.width*64 && hy < img->map.height*64 && distH <= distV)
		{
			ray.rx = hx;
			ray.ry = hy;
			dist = distH;
			wall_collor = 0x00FF0000;
		}
		// horizontal wall hit
		if (vx > 0 && vy > 0 && vx < img->map.width*64 && vy < img->map.height*64 && distV < distH)
		{
			ray.rx = vx;
			ray.ry = vy;
			dist = distV;
			wall_collor = 0x00550000;
		}
		// printf("i: %d, ray.rx: %f, ray.ry: %f\n", i, ray.rx, ray.ry);
		render_line(img, img->player.x, img->player.y, ray.rx, ray.ry, 0x00FF0000);
		//draw walls
		
		// fix fish eye
		float ca = img->player.angle - ray.ra;
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

void	print_screen(t_img *img)
{
	render_map(img);
	render_player(img);
	raycasterr(img);
	// my_mlx_pixel_put(img, img->player.x, img->player.y, 0x00FF0000);
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
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cats vs Cucumbers");
	if (win->win_ptr == NULL)
	{
		free(win->mlx_ptr);
		return (MLX_ERROR);
	}
	start_image(win);
	// mlx_mouse_hook(win->win_ptr, zoom, win);
	mlx_hook(win->win_ptr, 2, 1L << 0, &handle_input, win);
	// mlx_hook(win->win_ptr, 17, 1L << 0, &close_window, win);
	// mlx_expose_hook(win->win_ptr, (void *)start_image, win);
	mlx_loop(win->mlx_ptr);
	return (0);
}

void	init_game_params(t_win *win)
{
	win->mlx_ptr = NULL;
	win->img.player.x = 250;
	win->img.player.y = 350;
	win->img.player.cos = 5;
	win->img.player.sin = 0;
	win->img.player.angle = 0;
	win->img.map.width = 8;
	win->img.map.height = 8;
	win->img.map.map = malloc(sizeof(int *) * win->img.map.width);
	for (int i = 0; i < win->img.map.width; i++)
		win->img.map.map[i] = malloc(sizeof(int) * win->img.map.height);
	win->img.map.map[0][0] = 1;
	win->img.map.map[0][1] = 1;
	win->img.map.map[0][2] = 1;
	win->img.map.map[0][3] = 1;
	win->img.map.map[0][4] = 1;
	win->img.map.map[0][5] = 1;
	win->img.map.map[0][6] = 1;
	win->img.map.map[0][7] = 1;
	win->img.map.map[1][0] = 1;
	win->img.map.map[1][1] = 0;
	win->img.map.map[1][2] = 1;
	win->img.map.map[1][3] = 0;
	win->img.map.map[1][4] = 0;
	win->img.map.map[1][5] = 0;
	win->img.map.map[1][6] = 0;
	win->img.map.map[1][7] = 1;
	win->img.map.map[2][0] = 1;
	win->img.map.map[2][1] = 0;
	win->img.map.map[2][2] = 1;
	win->img.map.map[2][3] = 0;
	win->img.map.map[2][4] = 1;
	win->img.map.map[2][5] = 0;
	win->img.map.map[2][6] = 0;
	win->img.map.map[2][7] = 1;
	win->img.map.map[3][0] = 1;
	win->img.map.map[3][1] = 0;
	win->img.map.map[3][2] = 1;
	win->img.map.map[3][3] = 0;
	win->img.map.map[3][4] = 0;
	win->img.map.map[3][5] = 0;
	win->img.map.map[3][6] = 1;
	win->img.map.map[3][7] = 1;
	win->img.map.map[4][0] = 1;
	win->img.map.map[4][1] = 0;
	win->img.map.map[4][2] = 0;
	win->img.map.map[4][3] = 0;
	win->img.map.map[4][4] = 0;
	win->img.map.map[4][5] = 0;
	win->img.map.map[4][6] = 0;
	win->img.map.map[4][7] = 1;
	win->img.map.map[5][0] = 1;
	win->img.map.map[5][1] = 0;
	win->img.map.map[5][2] = 0;
	win->img.map.map[5][3] = 0;
	win->img.map.map[5][4] = 0;
	win->img.map.map[5][5] = 1;
	win->img.map.map[5][6] = 0;
	win->img.map.map[5][7] = 1;
	win->img.map.map[6][0] = 1;
	win->img.map.map[6][1] = 1;
	win->img.map.map[6][2] = 0;
	win->img.map.map[6][3] = 0;
	win->img.map.map[6][4] = 0;
	win->img.map.map[6][5] = 0;
	win->img.map.map[6][6] = 0;
	win->img.map.map[6][7] = 1;
	win->img.map.map[7][0] = 1;
	win->img.map.map[7][1] = 1;
	win->img.map.map[7][2] = 1;
	win->img.map.map[7][3] = 1;
	win->img.map.map[7][4] = 1;
	win->img.map.map[7][5] = 1;
	win->img.map.map[7][6] = 1;
	win->img.map.map[7][7] = 1;
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (1);
	if (init_game())
		return (1);
	return (0);
}

int	init_game(void)
{
	t_win	win;

	init_game_params(&win);
	if (!start_window(&win))
		return (1);
	return (0);
}
