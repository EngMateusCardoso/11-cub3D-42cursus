/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_validation_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:50:31 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 01:01:48 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	check_end(char **map, int x, int y, char c)
{
	return ((y > 0 && map[x][y + 1] == c && map[x][y - 1] == c)
	|| (x > 0 && map[x + 1] && map[x + 1][y] == c && map[x - 1][y] == c)
	|| (x > 0 && map[x - 1][y] == c && map[x][y + 1] == c)
	|| (x > 0 && y > 0 && map[x][y - 1] == c && map[x - 1][y] == c)
	|| (y > 0 && map[x + 1] && map[x + 1][y] == c && map[x][y - 1] == c)
	|| (map[x + 1] && map[x + 1][y] == c && map[x][y + 1] == c));
}

t_xy	get_player_position(char **map, int x, int y)
{
	t_xy	xy;

	xy.x = x - 1;
	xy.y = y - 1;
	while (map[++xy.x])
	{
		while (map[xy.x][++xy.y])
			if (ftex_is_in_set(map[xy.x][xy.y], VALID_PLAYER))
				break ;
		if (ftex_is_in_set(map[xy.x][xy.y], VALID_PLAYER))
			break ;
		xy.y = -1;
	}
	if (xy.y == -1)
		xy.y++;
	return (xy);
}

short int	inner_polygons_are_closed(char **map)
{
	char	*inner_wall;
	int		i;

	i = -1;
	while (map[++i])
	{
		inner_wall = ft_strchr(map[i], '9');
		if (inner_wall)
		{
			if (!slide_polygon(map, i, inner_wall - map[i], '@'))
				return (FALSE);
			i--;
		}
	}
	return (TRUE);
}
