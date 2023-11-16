/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:46:19 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/16 00:27:59 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3D.h"

short int	is_player_inside(char **map, int i, int j)
{
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '!')
			{
				while (map[i][j] && map[i][++j] == '!')
					continue ;
				if (ft_strchr(&map[i][j], '!'))
				{
					while (map[i][j] != '!')
					{
						if (ftex_is_in_set(map[i][j], VALID_PLAYER))
							return (TRUE);
						j++;
					}
				}
			}
			if (!map[i][j])
				j--;
		}
		j = -1;
	}
	return (FALSE);
}

short int	slide_polygon(char **map, int x, int y, char fill)
{
	while (1)
	{
		if (map[x + 1] && map[x + 1][y] == '9')
			map[x++][y] = fill;
		else if (y > 0 && map[x][y - 1] == '9')
			map[x][y--] = fill;
		else if (x > 0 && map[x - 1][y] == '9')
			map[x--][y] = fill;
		else if (map[x][y + 1] == '9')
			map[x][y++] = fill;
		else if (check_end(map, x, y, fill))
		{
			map[x][y] = fill;
			return (TRUE);
		}
		else
			return (FALSE);
		if (forked_polygon(map, x, y))
		{
			if (recursive_polygon(map, x, y))
				return (TRUE);
		}
	}
}

short int	recursive_polygon(char **map, int x, int y)
{
	if (map[x + 1] && map[x + 1][y] == '9')
		return (slide_polygon(map, x + 1, y, '!'));
	if (y > 0 && map[x][y - 1] == '9')
		return (slide_polygon(map, x, y - 1, '!'));
	if (x > 0 && map[x - 1][y] == '9')
		return (slide_polygon(map, x - 1, y, '!'));
	if (map[x][y + 1] == '9')
		return (slide_polygon(map, x, y + 1, '!'));
	return (FALSE);
}

short int	forked_polygon(char **map, int x, int y)
{
	int	i;

	i = 0;
	if (map[x][y + 1] == '9')
		i++;
	if (y > 0 && map[x][y - 1] == '9')
		i++;
	if (map[x + 1] && map[x + 1][y] == '9')
		i++;
	if (x > 0 && map[x - 1][y] == '9')
		i++;
	if (i < 2)
		return (FALSE);
	return (TRUE);
}

short int	walls_are_closed(char **map)
{
	t_xy		xy;
	short int	boolean;

	boolean = TRUE;
	xy = get_player_position(map, 0, 0);
	if (xy.x == 0 || map[xy.x][xy.y + 1] == '\0')
		return (FALSE);
	while (map[xy.x][xy.y] && map[xy.x][xy.y] != '9')
		xy.y++;
	boolean = slide_polygon(map, xy.x, xy.y, '!');
	if (boolean)
	{
		while (!is_player_inside(map, -1, -1))
		{
			tr_matrix(map, "!", "@");
			xy = get_player_position(map, 0, 0);
			if (xy.x == 0 || !ft_strchr(&map[xy.x][xy.y], '9'))
				return (FALSE);
			while (map[xy.x][xy.y] && map[xy.x][xy.y] != '9')
				xy.y++;
			boolean = slide_polygon(map, xy.x, xy.y, '!');
		}
		return (boolean);
	}
	return (FALSE);
}
