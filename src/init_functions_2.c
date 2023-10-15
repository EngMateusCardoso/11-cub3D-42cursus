/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:23:58 by matcardo          #+#    #+#             */
/*   Updated: 2023/10/14 19:00:05 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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
		while (line[i] == ' ')
			i++;
		if (line[i] == 'C')
			win->img.ceiling_color = get_color(line);
		else if (line[i] == 'F')
			win->img.floor_color = get_color(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	get_color(char *line)
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
