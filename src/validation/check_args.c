/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:16:04 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/11 01:42:08 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

short int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		printf(E_ARG);
		return (FALSE);
	}
	if (!is_valid_file_extension(argv[1]))
	{
		printf(E_EXT, argv[1]);
		return (FALSE);
	}
	if (!is_valid_file(argv[1]))
	{
		printf(E_FILE_404, argv[1]);
		return (FALSE);
	}
	if (!is_valid_map(argv[1]))
	{
		return (FALSE);
	}
	return (TRUE);
}

short int	is_valid_file_extension(char *str)
{
	size_t	offset;

	offset = ft_strlen(str) - 4;
	if (ft_strncmp(".cub", str + offset, 5) == 0)
		return (TRUE);
	return (FALSE);
}

short int	is_valid_file(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	close(fd);
	return (TRUE);
}

short int	is_valid_map(char *str)
{
	t_params	params;

	init_params(&params);
	params.map = trim_map_array(open(str, O_RDONLY));
	params.dev_map = trim_map_array(open(str, O_RDONLY));
	if (!params.map)
		return (print_error(E_EMPTMAP, NULL, NULL));
	if (!files_validation(&params, str))
		return (map_validation_failed(&params));
	if (!map_validation(params.map))
		return (map_validation_failed(&params));
	print_color_map(params.map);
	free_params_validation(&params);
	return (TRUE);
}
