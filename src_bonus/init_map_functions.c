/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:12:32 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 03:13:41 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3D.h"

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
		if (is_map_line(line))
		{
			win->img.map.height++;
			if (win->img.map.width < (int)ft_strlen(line) - 1)
				win->img.map.width = ft_strlen(line) - 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	init_map_scale(win);
}

void	init_map_scale(t_win *win)
{
	if (win->img.map.width >= WIN_WIDTH / CUBE_SIZE || \
		win->img.map.height >= WIN_WIDTH / CUBE_SIZE)
	{
		if (win->img.map.width >= win->img.map.height)
			win->img.map.minimap_scale = WIN_WIDTH * MAX_MAP_SCALE / \
				(CUBE_SIZE * win->img.map.width);
		else
			win->img.map.minimap_scale = WIN_WIDTH * MAX_MAP_SCALE / \
				(CUBE_SIZE * win->img.map.height);
	}
	else
		win->img.map.minimap_scale = MAX_MAP_SCALE;
}

void	init_map(t_win *win, char *file)
{
	int		fd;
	char	*line;
	int		i;

	win->img.map.map = malloc(sizeof(char *) * (win->img.map.height + 1));
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (is_map_line(line))
		{
			win->img.map.map[i] = ft_strdup(line);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	win->img.map.map[i] = NULL;
	free(line);
	close(fd);
}

short int	is_map_line(char *line)
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
