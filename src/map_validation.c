/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:38:01 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/10 17:41:18 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

short int	count_player(char **map)
{
	int	i;
	int	j;
	int	player_char;

	i = -1;
	j = -1;
	player_char = 0;
	while (map[++i])
	{
		while (map[i][++j])
			if (ftex_is_in_set(map[i][j], VALID_PLAYER))
				player_char++;
		j = -1;
	}
	return (player_char);
}

short int	char_is_next_to(char **map, int x, int y, char c)
{
	if ((x > 0 && y > 0 && map[x - 1][y - 1] == c)
	|| (y > 0 && map[x][y - 1] == c)
	|| (map[x + 1] && y > 0 && map[x + 1][y - 1] == c)
	|| (x > 0 && map[x - 1][y] == c)
	|| (map[x + 1] && map[x + 1][y] == c)
	|| (x > 0 && map[x - 1][y + 1] == c)
	|| map[x][y + 1] == c
	|| (map[x + 1] && map[x + 1][y + 1] == c))
		return (TRUE);
	return (FALSE);
}

void	clear_around_map(char **map)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '1' && !char_is_next_to(map, i, j, '0')
			&& (!char_is_next_to(map, i, j, 'E')
			&& !char_is_next_to(map, i, j, 'W')
			&& !char_is_next_to(map, i, j, 'S')
			&& !char_is_next_to(map, i, j, 'N')))
				map[i][j] = ' ';
		}
		j = -1;
	}
}

char	validate_map_chars(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
			if (!ftex_is_in_set(map[i][j], VALID_MAP_CHARS))
				return (map[i][j]);
		j = -1;
	}
	return ('\0');
}

short int	map_validation(char **map)
{
	short int	player;
	char		invalid;

	player = count_player(map);
	if (player < 1)
		return (print_error(STR_PLAYER_NOT_FOUND, NULL, NULL));
	else if (player > 1)
		return (print_error(STR_MULTI_PLAYER, NULL, NULL));
	clear_around_map(map);
	invalid = validate_map_chars(map);
	if (invalid)
		return (print_error_char(STR_INVALID_MAP_CHAR, invalid));
	outline_walls(map);
	outline_useless_walls(map);
	if (!walls_are_closed(map))
		return (print_error(STR_MAP_WALLS_OPEN1, NULL, NULL));
	remove_out_characters(map);
	if (!inner_polygons_are_closed(map))
		return (print_error(STR_MAP_WALLS_OPEN2, NULL, NULL));
	if (player_out_of_map(map))
		return (print_error(STR_PLAYER_OUT, NULL, NULL));
	tr_matrix(map, "@", "1");
	tr_matrix(map, "!", "1");
	return (TRUE);
}