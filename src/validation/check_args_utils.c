/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:33:37 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 01:23:07 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

short int	print_error(char *error, char *param, char *set)
{
	if (set && param)
		printf(error, param, set);
	else if (set)
		printf(error, set);
	else if (param)
		printf(error, param);
	else
		printf("%s", error);
	return (FALSE);
}

short int	print_error_char(char *error, char param)
{
	if (param)
		printf(error, param);
	else
		printf("%s", error);
	return (FALSE);
}

int	istrimmed(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (TRUE);
		set++;
	}
	return (FALSE);
}

int	strsize(char *str, char *set)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (!istrimmed(*str++, set))
			i++;
	}
	return (i);
}

void	print_color_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				printf("\e[1;91m%c\e[0m", map[i][j]);
			else if (map[i][j] == '0')
				printf("\e[1;94m%c\e[0m", map[i][j]);
			else if (ftex_is_in_set(map[i][j], "NSEW"))
				printf("\e[1;92m%c\e[0m", map[i][j]);
			else if (map[i][j] == ' ' || map[i][j] == '\t')
				printf("%c", ' ');
			else
				printf("\e[1;93m%c\e[0m", map[i][j]);
		}
		printf("\n");
		j = -1;
	}
}
