/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:16:04 by matcardo          #+#    #+#             */
/*   Updated: 2023/09/07 14:39:11 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

short int	is_valid_file_extension(char *str)
{
	size_t	offset;

	offset = ft_strlen(str) - 4;
	if (ft_strncmp(".cub", str + offset, 5) == 0)
		return (TRUE);
	return (FALSE);
}

short int	check_args(int argc, char **argv)
{
	return (TRUE);
	if (argc != 2)
	{
		printf(STR_INVALID_ARG);
		return (FALSE);
	}
	if (!is_valid_file_extension(argv[1]))
	{
		printf(STR_INVALID_MAP, argv[1]);
		return (FALSE);
	}
	// Verificar se encontra e abre o arquivo 
	// Verificar se o arquivo é vazio
	// Verificar se o arquivo é legível
	// Verificações do corpo do arquivo coerencia dos argumentos e do mapa
	return (TRUE);
}
