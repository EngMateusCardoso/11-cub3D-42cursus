/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:12:32 by matcardo          #+#    #+#             */
/*   Updated: 2023/10/14 14:13:06 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"


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
