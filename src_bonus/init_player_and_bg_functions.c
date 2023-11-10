/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_and_background_functions.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 01:34:59 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/06 01:35:57 by matcardo         ###   ########.fr       */
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
		if (is_map_line(line))
		{
			init_player_position_line(win, line, i);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
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

void	init_roof_and_ceiling_color(t_win *win, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == 'C')
			win->img.ceiling_color = get_color_in_line(line);
		else if (line[i] == 'F')
			win->img.floor_color = get_color_in_line(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

int	get_color_in_line(char *line)
{
	int		i;
	int		color;
	int		r;
	int		g;
	int		b;

	i = 0;
	while (line[i] == ' ' || line[i] == 'C' || line[i] == 'F')
		i++;
	i++;
	r = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	g = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	b = ft_atoi(line + i);
	color = 0 << 24 | r << 16 | g << 8 | b;
	return (color);
}
