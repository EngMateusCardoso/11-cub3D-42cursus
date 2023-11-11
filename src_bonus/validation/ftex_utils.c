/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftex_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:36:01 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 03:14:32 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3D.h"

int	is_in_del(char c, char *del)
{
	int	i;

	i = -1;
	while (del[++i])
	{
		if (c == del[i])
			return (i);
	}
	return (-1);
}

char	find_new(char *ret, int index)
{
	int	len;

	len = ft_strlen(ret);
	if (index > len - 1)
		return (ret[len - 1]);
	else
		return (ret[index]);
}

char	*ftex_strerase(char *str, char *set)
{
	size_t	size;
	char	*res;

	if (!str)
		return (NULL);
	size = strsize(str, set);
	res = (char *)malloc(sizeof(char) * size + 1);
	while (*str)
	{
		if (!istrimmed(*str, set))
			*res++ = *str++;
		else
			str++;
	}
	*res = '\0';
	return (res - size);
}

short int	ftex_is_in_set(char c, char *set)
{
	if (!set)
		return (FALSE);
	while (*set)
	{
		if (c == *set)
			return (TRUE);
		set++;
	}
	return (FALSE);
}

void	ftex_tr(char *str, char *del, char *replace)
{
	int		index;
	int		i;

	if (!str || !del || !replace)
		return ;
	i = -1;
	while (str[++i])
	{
		index = is_in_del(str[i], del);
		if (index == -1)
			continue ;
		str[i] = find_new(replace, index);
	}
}
