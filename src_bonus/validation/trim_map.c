/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:06:12 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 01:02:10 by thabeck-         ###   ########.fr       */
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

	if (fd == -1)
		return (NULL);
	tmp = get_next_line(fd);
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
	close(fd);
	free(line);
	return (ret);
}
