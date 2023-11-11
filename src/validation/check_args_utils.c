/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:33:37 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 20:17:04 by thabeck-         ###   ########.fr       */
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
