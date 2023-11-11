/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:55:27 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 01:18:10 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	comma_counter(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}

int	get_color(int r, int g, int b)
{
	int	rgb;

	rgb = 0;
	rgb += (r & 0xFF) << 16;
	rgb += (g & 0XFF) << 8;
	rgb += (b & 0XFF);
	return (rgb);
}

short int	is_str_number(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (FALSE);
			j++;
		}
		i++;
		j = 0;
	}
	return (TRUE);
}

void	gnl_purge(char *tmp, int fd)
{
	if (fd == -1)
		return ;
	free(tmp);
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	close (fd);
}

int	str_maxsize(char **matrix)
{
	int	i;
	int	size;
	int	maxsize;

	maxsize = 0;
	i = -1;
	while (matrix[++i])
	{
		size = ft_strlen(matrix[i]);
		if (size > maxsize)
			maxsize = size;
	}
	return (maxsize);
}
