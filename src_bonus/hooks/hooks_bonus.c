/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:25 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/17 20:13:40 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3D_bonus.h"

void    active_doors()
{
	printf("oiiii");
}

int	handle_input(int keysys, t_win *win)
{
	if (keysys == KEY_ESC)
		close_window(win);
	if (keysys == KEY_W || keysys == KEY_A || \
		keysys == KEY_S || keysys == KEY_D)
		move_player(keysys, win);
	else if (keysys == KEY_LEFT || keysys == KEY_RIGHT)
		rotate_player(keysys, win);
	else if (keysys == KEY_SPACE)
		active_doors();
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

void	free_textures(int	**textures)
{
	int	i;

	i = 0;
	while (textures[i])
	{
		free(textures[i]);
		i++;
	}
	free(textures);
}

int	close_window(t_win *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	mlx_destroy_display(win->mlx_ptr);
	free(win->mlx_ptr);
	free_map(win->img.map.map);
	free_textures(win->img.textures[NO]);
	free_textures(win->img.textures[SO]);
	free_textures(win->img.textures[WE]);
	free_textures(win->img.textures[EA]);
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
