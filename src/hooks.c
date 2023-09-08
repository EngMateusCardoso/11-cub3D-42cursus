/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:25 by matcardo          #+#    #+#             */
/*   Updated: 2023/09/08 10:48:28 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	move_player(int keysys, t_win *win)
{
	if (keysys == 119)
	{
		win->img.player.x += win->img.player.cos;
		win->img.player.y += win->img.player.sin;
	}
	else if (keysys == 97)
	{
		win->img.player.x += win->img.player.sin;
		win->img.player.y -= win->img.player.cos;
	}
	else if (keysys == 115)
	{
		win->img.player.x -= win->img.player.cos;
		win->img.player.y -= win->img.player.sin;
	}
	else if (keysys == 100)
	{
		win->img.player.x -= win->img.player.sin;
		win->img.player.y += win->img.player.cos;
	}
}

void	rotate_player(int keysys, t_win *win)
{
	if (keysys == 65361)
	{
		win->img.player.angle -= 0.1;
		if (win->img.player.angle < 0)
			win->img.player.angle += 2 * PI;
	}
	else if (keysys == 65363)
	{
		win->img.player.angle += 0.1;
		if (win->img.player.angle > 2 * PI)
			win->img.player.angle -= 2 * PI;
	}
	win->img.player.cos = cos(win->img.player.angle) * 5;
	win->img.player.sin = sin(win->img.player.angle) * 5;
}

void	close_window()
{
	// mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

int	handle_input(int keysys, t_win *win)
{
	if (keysys == 65307)
		close_window();
	if (keysys == 119 || keysys == 97 || keysys == 115 || keysys == 100)
		move_player(keysys, win);
	else if (keysys == 65361 || keysys == 65363)
		rotate_player(keysys, win);
	start_image(win);
	return (0);
}
