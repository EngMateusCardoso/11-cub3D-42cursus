/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:25 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 15:14:18 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3D.h"

int	handle_input(int keysys, t_win *win)
{
	if (keysys == KEY_ESC)
		close_window(win);
	if (keysys == KEY_W || keysys == KEY_A || \
		keysys == KEY_S || keysys == KEY_D)
		move_player(keysys, win);
	else if (keysys == KEY_LEFT || keysys == KEY_RIGHT)
		rotate_player(keysys, win);
	start_image(win);
	return (0);
}

void	rotate_player(int keysys, t_win *win)
{
	if (keysys == KEY_LEFT)
	{
		win->img.player.angle -= 0.1;
		if (win->img.player.angle < 0)
			win->img.player.angle += 2 * PI;
	}
	else if (keysys == KEY_RIGHT)
	{
		win->img.player.angle += 0.1;
		if (win->img.player.angle > 2 * PI)
			win->img.player.angle -= 2 * PI;
	}
	win->img.player.cos = cos(win->img.player.angle) * 5;
	win->img.player.sin = sin(win->img.player.angle) * 5;
}


static void	mouse_move_x(int x, int mid_x, int mid_y, t_win *win)
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

static void	mouse_move_y(int y, int mid_x, int mid_y, t_win *win)
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

int	close_window(t_win *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	mlx_destroy_display(win->mlx_ptr);
	free(win->mlx_ptr);
	free_map(win->img.map.map);
	exit(0);
	return (0);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
