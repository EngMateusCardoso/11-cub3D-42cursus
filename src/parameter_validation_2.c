/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_validation_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:54:07 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/10 19:01:23 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	tr_matrix(char **matrix, char *del, char *replace)
{
	int	i;

	i = -1;
	while (matrix[++i])
		ftex_tr(matrix[i], del, replace);
}

char	*join_color_set(char **matrix)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = -1;
	while (matrix[++i])
		continue ;
	if (i < 2 || !ft_strchr(matrix[1], ','))
		return (matrix[1]);
	i = 1;
	ret = ft_strdup(matrix[1]);
	while (matrix[++i])
	{
		tmp = ret;
		ret = ft_strjoin(ret, matrix[i]);
		free(tmp);
	}
	free(matrix[1]);
	return (ret);
}

short int	validate_color_set(char *param, char *set, int *store)
{
	char	**rgb;
	char	*tmp;
	int		i;
	short int	valid;

	valid = TRUE;
	if (comma_counter(set) != 2)
		return (print_error(STR_RGB_COLOR, param, set));
	if (*store != -1)
		return (print_error(STR_DUPLICATED_COLOR, param, NULL));
	tmp = ftex_strerase(set, " \n");
	rgb = ft_split(tmp, ',');
	i = -1;
	while (rgb[++i])
		if (ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0)
			valid = print_error(STR_OUT_RANGE_COLOR, param, set);
	if (i != 3)
		valid = print_error(STR_RGB_COLOR, param, set);
	
	if (!is_str_number(rgb) && valid)
		valid = print_error(STR_NOT_NUMERIC_COLOR, param, set);
	if (valid)
		*store = get_color(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free(tmp);
	free_map(rgb);
	return (valid);
}
