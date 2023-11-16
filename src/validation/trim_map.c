/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:06:12 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/15 22:22:25 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

char	**set_padding(char **matrix, int maxsize)
{
	int		size;
	int		i;
	char	*tmp;

	i = -1;
	while (matrix[++i])
	{
		size = ft_strlen(matrix[i]);
		if (size < maxsize)
		{
			tmp = malloc(sizeof(char) * maxsize + 1);
			ft_strlcpy(tmp, matrix[i], size + 1);
			ft_memset(tmp + size, ' ', maxsize - size);
			tmp[maxsize] = '\0';
			free(matrix[i]);
			matrix[i] = tmp;
		}
	}
	return (matrix);
}

char	**trim_map_array(int fd)
{
	char	*line;
	char	*tmp;
	char	**ret;

	tmp = get_next_line(fd);
	if (!tmp)
		return (NULL);
	while (ftex_is_in_set(*tmp, VALID_ID))
	{
		free(tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			return (NULL);
	}
	line = ft_strdup("");
	while (tmp)
	{
		line = ft_strmerge(line, tmp);
		tmp = get_next_line(fd);
	}
	ret = ft_split(line, '\n');
	ret = set_padding(ret, str_maxsize(ret));
	free(line);
	return (ret);
}
