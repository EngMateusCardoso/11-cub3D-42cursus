/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:40:54 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 01:20:48 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

short int	is_border(char **map, int x, int y, char c)
{
	if (x == 0 || y == 0 || map[x][y + 1] == '\0' || map[x + 1] == NULL)
		return (TRUE);
	if (map[x - 1][y - 1] == c
	|| map[x][y - 1] == c
	|| map[x + 1][y - 1] == c
	|| map[x - 1][y] == c
	|| map[x + 1][y] == c
	|| map[x - 1][y + 1] == c
	|| map[x][y + 1] == c
	|| map[x + 1][y + 1] == c)
		return (TRUE);
	return (FALSE);
}

void	outline_walls(char **map)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (map[++x])
	{
		while (map[x][++y])
			if (map[x][y] == '1')
				if (is_border(map, x, y, ' '))
					map[x][y] = '9';
		y = -1;
	}
}

void	outline_useless_walls(char **map)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (map[++x])
	{
		while (map[x][++y])
			if (map[x][y] == '!')
				if (!is_border(map, x, y, '0')
					&& !is_border(map, x, y, '1'))
					map[x][y] = '#';
		y = -1;
	}
}

void	remove_out_characters(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j] && map[i][j] != '!')
			map[i][j] = ' ';
		j = ft_strlen(map[i]);
		while (--j >= 0 && map[i][j] != '!')
			map[i][j] = ' ';
		j = -1;
	}
}

short int	player_out_of_map(char **map)
{
	t_xy	xy;

	xy = get_player_position(map, 0, 0);
	if (map[xy.x - 1][xy.y] && map[xy.x][xy.y - 1] \
		&& map[xy.x + 1][xy.y] && map[xy.x][xy.y + 1] \
		&& (map[xy.x - 1][xy.y] == ' ' || map[xy.x - 1][xy.y] == '\t'
		|| map[xy.x + 1][xy.y] == ' ' || map[xy.x + 1][xy.y] == '\t'
		|| map[xy.x][xy.y - 1] == ' ' || map[xy.x][xy.y - 1] == '\t'
		|| map[xy.x][xy.y + 1] == ' ' || map[xy.x][xy.y + 1] == '\t'))
		return (TRUE);
	return (FALSE);
}
