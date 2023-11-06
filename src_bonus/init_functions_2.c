/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:23:58 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/05 23:59:37 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	init_roof_and_ceiling_color(t_win *win, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == 'C')
			win->img.ceiling_color = get_color_in_line(line);
		else if (line[i] == 'F')
			win->img.floor_color = get_color_in_line(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

int	get_color_in_line(char *line)
{
	int		i;
	int		color;
	int		r;
	int		g;
	int		b;

	i = 0;
	while (line[i] == ' ' || line[i] == 'C' || line[i] == 'F')
		i++;
	i++;
	r = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	g = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	b = ft_atoi(line + i);
	color = 0 << 24 | r << 16 | g << 8 | b;
	return (color);
}

void	init_textures(t_win *win, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == 'N' && line[i + 1] == 'O')
			get_texture(line, win, NO);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			get_texture(line, win, SO);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			get_texture(line, win, WE);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			get_texture(line, win, EA);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	get_texture(char *line, t_win *win, int direction)
{
	char	*path;
	t_img	img;
	int		i;
	int		j;

	path = path_to_texture(line);
	img.img_ptr = mlx_xpm_file_to_image(win->mlx_ptr, path, \
		&img.img_width, &img.img_height);
	free(path);
	if (!img.img_ptr)
	{
		printf("Error\nInvalid texture path\n");
		exit(1);
	}
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, \
		&img.line_len, &img.endian);
	win->img.textures[direction] = malloc(sizeof(int *) * img.img_width);
	i = -1;
	while (++i < img.img_width)
		win->img.textures[direction][i] = malloc(sizeof(int) * img.img_height);
	i = -1;
	while (++i < img.img_width)
	{
		j = -1;
		while (++j < img.img_height)
			win->img.textures[direction][i][j] = \
				img.data[i + j * img.img_height];
	}
	win->img.texture_width[direction] = img.img_width;
	win->img.texture_height[direction] = img.img_height;
	mlx_destroy_image(win->mlx_ptr, img.img_ptr);
}

char	*path_to_texture(char *line)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (line[i] != '.')
		i++;
	j = i;
	while (line[j] != ' ' && line[j] != '\n')
		j++;
	path = malloc(sizeof(char) * (j - i + 2));
	j = 0;
	while (line[i] != ' ' && line[i] != '\n')
	{
		path[j] = line[i];
		i++;
		j++;
	}
	path[j] = '\0';
	return (path);
}
