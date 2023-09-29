/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:32:32 by matcardo          #+#    #+#             */
/*   Updated: 2023/09/29 16:19:21 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line(int fd, char *backup, size_t buffer_size)
{
	char	*line;
	char	*buffer;
	int		line_lenght;

	if (backup)
		line = ft_strdup(backup);
	else
		line = ft_strdup("");
	buffer = malloc((buffer_size + 1) * sizeof(char));
	line_lenght = 1;
	while (!ft_strchr(line, '\n') && line_lenght)
	{
		line_lenght = read(fd, buffer, buffer_size);
		if (line_lenght < 0)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[line_lenght] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*take_backup(char *line, char *old_backup)
{
	char	*backup;
	char	*end;

	free(old_backup);
	end = ft_strchr(line, '\n');
	if (!end)
		return (NULL);
	backup = ft_strdup(end + 1);
	*(end + 1) = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(fd, backup, BUFFER_SIZE);
	if (!line)
	{
		free(backup);
		return (NULL);
	}
	backup = take_backup(line, backup);
	if (!*line)
	{
		free(backup);
		free(line);
		return (NULL);
	}
	return (line);
}
