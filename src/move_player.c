/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:06:39 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/10 19:48:52 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	move_player(int keysys, t_win *win)
{
	if (keysys == KEY_W)
		move_player_forward(win);
	else if (keysys == KEY_A)
		move_player_left(win);
	else if (keysys == KEY_S)
		move_player_backward(win);
	else if (keysys == KEY_D)
		move_player_right(win);
}

void	move_player_forward(t_win *win)
{
	int	player_map_position_x;
	int	player_map_position_y;
	int	player_map_position_forward_x;
	int	player_map_position_forward_y;

	player_map_position_x = (int)win->img.player.x / CUBE_SIZE;
	player_map_position_y = (int)win->img.player.y / CUBE_SIZE;
	player_map_position_forward_x
		= (int)(win->img.player.x + win->img.player.cos * 4) / CUBE_SIZE;
	player_map_position_forward_y
		= (int)(win->img.player.y + win->img.player.sin * 4) / CUBE_SIZE;
	if (win->img.map.map[player_map_position_y][player_map_position_forward_x]
		!= '1')
		win->img.player.x += win->img.player.cos;
	if (win->img.map.map[player_map_position_forward_y][player_map_position_x]
		!= '1')
		win->img.player.y += win->img.player.sin;
}

void	move_player_backward(t_win *win)
{
	int	player_map_position_x;
	int	player_map_position_y;
	int	player_map_position_backward_x;
	int	player_map_position_backward_y;

	player_map_position_x = (int)win->img.player.x / CUBE_SIZE;
	player_map_position_y = (int)win->img.player.y / CUBE_SIZE;
	player_map_position_backward_x
		= (int)(win->img.player.x - win->img.player.cos * 4) / CUBE_SIZE;
	player_map_position_backward_y
		= (int)(win->img.player.y - win->img.player.sin * 4) / CUBE_SIZE;
	if (win->img.map.map[player_map_position_y][player_map_position_backward_x]
		!= '1')
		win->img.player.x -= win->img.player.cos;
	if (win->img.map.map[player_map_position_backward_y][player_map_position_x]
		!= '1')
		win->img.player.y -= win->img.player.sin;
}

void	move_player_right(t_win *win)
{
	int	player_map_position_x;
	int	player_map_position_y;
	int	player_map_position_left_x;
	int	player_map_position_left_y;

	player_map_position_x = (int)win->img.player.x / CUBE_SIZE;
	player_map_position_y = (int)win->img.player.y / CUBE_SIZE;
	player_map_position_left_x
		= (int)(win->img.player.x - win->img.player.sin * 4) / CUBE_SIZE;
	player_map_position_left_y
		= (int)(win->img.player.y + win->img.player.cos * 4) / CUBE_SIZE;
	if (win->img.map.map[player_map_position_y][player_map_position_left_x]
		!= '1')
		win->img.player.x -= win->img.player.sin;
	if (win->img.map.map[player_map_position_left_y][player_map_position_x]
		!= '1')
		win->img.player.y += win->img.player.cos;
}

void	move_player_left(t_win *win)
{
	int	player_map_position_x;
	int	player_map_position_y;
	int	player_map_position_right_x;
	int	player_map_position_right_y;

	player_map_position_x = (int)win->img.player.x / CUBE_SIZE;
	player_map_position_y = (int)win->img.player.y / CUBE_SIZE;
	player_map_position_right_x
		= (int)(win->img.player.x + win->img.player.sin * 4) / CUBE_SIZE;
	player_map_position_right_y
		= (int)(win->img.player.y - win->img.player.cos * 4) / CUBE_SIZE;
	if (win->img.map.map[player_map_position_y][player_map_position_right_x]
		!= '1')
		win->img.player.x += win->img.player.sin;
	if (win->img.map.map[player_map_position_right_y][player_map_position_x]
		!= '1')
		win->img.player.y -= win->img.player.cos;
}
