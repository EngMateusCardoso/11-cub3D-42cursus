/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:40:03 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 16:30:24 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (1);
	if (init_game(argv[1]))
		return (1);
	return (0);
}

int	init_game(char *file)
{
	t_win	win;

	init_game_params(&win, file);
	if (!start_window(&win, file))
		return (1);
	return (0);
}

void	init_game_params(t_win *win, char *file)
{
	win->mlx_ptr = NULL;
	init_map_dimensions(win, file);
	init_map(win, file);
	init_player_position(win, file);
	init_roof_and_ceiling_color(win, file);
}

int	start_window(t_win *win, char *file)
{
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
		return (MLX_ERROR);
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, \
		WIN_TITLE);
	if (win->win_ptr == NULL)
	{
		free(win->mlx_ptr);
		return (MLX_ERROR);
	}
	init_textures(win, file);
	start_image(win);
	mlx_hook(win->win_ptr, 2, 1L << 0, &handle_input, win);
	mlx_hook(win->win_ptr, 17, 1L << 0, &close_window, win);
	mlx_expose_hook(win->win_ptr, (void *)start_image, win);
	mlx_loop(win->mlx_ptr);
	return (0);
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
