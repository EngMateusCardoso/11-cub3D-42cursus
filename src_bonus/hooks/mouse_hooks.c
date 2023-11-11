/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:50:40 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 15:56:30 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3D.h"

void	mouse_move_x(int x, int mid_x, int mid_y, t_win *win)
{
	static int	new_x;

	if (x != new_x)
	{
		if (new_x > x)
		{
			win->img.player.angle -= 0.01;
			if (win->img.player.angle < 0)
				win->img.player.angle += 2 * PI;
		}
		else if (new_x < x)
		{
			win->img.player.angle += 0.01;
			if (win->img.player.angle > 2 * PI)
				win->img.player.angle -= 2 * PI;
		}
		mlx_mouse_move(win->mlx_ptr, win->win_ptr, mid_x, mid_y);
		new_x = mid_x;
	}
}

void	mouse_move_y(int y, int mid_x, int mid_y, t_win *win)
{
	static int	new_y;

	if (y != new_y)
	{
		if (y > mid_y || y < mid_y)
			mlx_mouse_move(win->mlx_ptr, win->win_ptr, mid_x, mid_y);
		new_y = mid_y;
	}
}

int	mouse_move(int x, int y, t_win *win)
{
	int	mid_x;
	int	mid_y;

	mid_x = WIN_WIDTH / 2;
	mid_y = WIN_HEIGHT / 2;
	if (abs(mid_x - x) > 540 && abs(mid_y - y) < 50)
	{
		mouse_move_x(x, mid_x, mid_y, win);
		mouse_move_y(y, mid_x, mid_y, win);
		win->img.player.cos = cos(win->img.player.angle) * 3;
		win->img.player.sin = sin(win->img.player.angle) * 3;
		start_image(win);
	}
	return (0);
}

int	handle_mouse(int keysys, int x, int y, t_win *win)
{
	if (keysys && y)
	{
		if (x > WIN_WIDTH / 2)
			rotate_player(KEY_RIGHT, win);
		else if (x < 250)
			rotate_player(KEY_LEFT, win);
	}
	start_image(win);
	return (0);
}
