/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:40:03 by matcardo          #+#    #+#             */
/*   Updated: 2023/09/07 22:55:55 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	render_line(t_img *img, int x, int y, float angle)
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
			my_mlx_pixel_put(img, x * 64 + i, y * 64 + j, 0x00FFFFFF);
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
	render_line(img, img->player.x, img->player.y, img->player.angle);
	render_line(img, img->player.x, img->player.y, img->player.angle + PI / 2);
}

void	print_screen(t_img *img)
{
	render_map(img);
	render_player(img);
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
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Fract-ol");
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
	win->img.map.map[2][4] = 0;
	win->img.map.map[2][5] = 0;
	win->img.map.map[2][6] = 0;
	win->img.map.map[2][7] = 1;
	win->img.map.map[3][0] = 1;
	win->img.map.map[3][1] = 0;
	win->img.map.map[3][2] = 1;
	win->img.map.map[3][3] = 0;
	win->img.map.map[3][4] = 0;
	win->img.map.map[3][5] = 0;
	win->img.map.map[3][6] = 0;
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
	win->img.map.map[6][1] = 0;
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

int	init_game(void)
{
	t_win	win;

	printf("init_game\n");
	init_game_params(&win);
	if (!start_window(&win))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (1);
	if (init_game())
		return (1);
	return (0);
}
