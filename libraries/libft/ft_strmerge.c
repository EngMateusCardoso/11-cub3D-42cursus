/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:43:05 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/06 00:45:24 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmerge(char *s1, char *s2)
{
	char	*str;
	size_t	size;

	if (!s1 || !s2)
	{
		ft_free_pointer((void *)&s1);
		ft_free_pointer((void *)&s2);
		return (NULL);
	}
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, size);
	ft_free_pointer((void *)&s1);
	ft_free_pointer((void *)&s2);
	return (str);
}
