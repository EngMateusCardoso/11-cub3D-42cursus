/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_validation_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:01:16 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 01:48:23 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

short int	check_parameter_matrix(t_params *p, char **m, char *f, char *t)
{
	short int	valid;

	valid = FALSE;
	m = ft_split(t, ' ');
	m[1] = join_color_set(m);
	if (!ft_strncmp(m[0], "NO", 2) && ft_strlen(m[0]) == 2)
		valid = validate_texture_file(m[0], m[1], &p->north);
	else if (!ft_strncmp(m[0], "SO", 2) && ft_strlen(m[0]) == 2)
		valid = validate_texture_file(m[0], m[1], &p->south);
	else if (!ft_strncmp(m[0], "EA", 2) && ft_strlen(m[0]) == 2)
		valid = validate_texture_file(m[0], m[1], &p->east);
	else if (!ft_strncmp(m[0], "WE", 2) && ft_strlen(m[0]) == 2)
		valid = validate_texture_file(m[0], m[1], &p->west);
	else if (!ft_strncmp(m[0], "F", 1) && ft_strlen(m[0]) == 1)
		valid = validate_color_set(m[0], m[1], &p->floor_color);
	else if (!ft_strncmp(m[0], "C", 1) && ft_strlen(m[0]) == 1)
		valid = validate_color_set(m[0], m[1], &p->ceil_color);
	else
		print_error(E_INVID, m[0], f);
	free_map(m);
	return (valid);
}

short int	is_first_char_invalid(int fd, char **tmp)
{
	int	i;

	i = 0;
	if (*tmp == NULL)
		return (FALSE);
	while ((*tmp)[i] == ' ' || (*tmp)[i] == '\t')
		++i;
	if (!ftex_is_in_set((*tmp)[i], VALID_ID))
	{
		free(*tmp);
		*tmp = get_next_line(fd);
		return (TRUE);
	}
	return (FALSE);
}

short int	check_all_params(t_params *params)
{
	if (!ftex_is_in_set((params->dev_map)[0][0], VALID_GLOBAL_ID))
		return (print_error(E_INVID, (params->dev_map)[0], NULL));
	if (params->north == NULL)
		return (print_error(E_NOTEX, "NO", NULL));
	if (params->east == NULL)
		return (print_error(E_NOTEX, "EA", NULL));
	if (params->south == NULL)
		return (print_error(E_NOTEX, "SO", NULL));
	if (params->west == NULL)
		return (print_error(E_NOTEX, "WE", NULL));
	if (params->ceil_color == -1)
		return (print_error(E_NOCOLOR, "C", NULL));
	if (params->floor_color == -1)
		return (print_error(E_NOCOLOR, "F", NULL));
	return (TRUE);
}

short int	validate_texture_file(char *param, char *file, char **store)
{
	int		fd;
	char	*dot;

	if (*store)
		return (print_error(E_DUPTEX, param, NULL));
	if (!file)
		return (FALSE);
	dot = ft_strrchr(file, '.');
	if (!dot || ft_strncmp(dot, ".xpm\n", 5))
		return (print_error(E_EXTTEX, param, file));
	file[ft_strlen(file) - 1] = '\0';
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(E_TEX_404, param, file));
	close(fd);
	*store = ft_strdup(file);
	return (TRUE);
}

short int	files_validation(t_params *params, char *file)
{
	int			fd;
	char		*tmp;
	char		**parameters;
	short int	valid;

	valid = TRUE;
	parameters = NULL;
	fd = open(file, O_RDONLY);
	tmp = get_next_line(fd);
	if (!tmp || fd == -1)
		return (FALSE);
	while (tmp && valid)
	{
		if (is_first_char_invalid(fd, &tmp))
			break ;
		if (*tmp != '\n')
			valid = check_parameter_matrix(params, parameters, file, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	gnl_purge(tmp, fd);
	if (valid)
		valid = check_all_params(params);
	return (valid);
}
