/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:16:04 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/06 00:32:25 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

short int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		printf(STR_INVALID_ARG);
		return (FALSE);
	}
	if (!is_valid_file_extension(argv[1]))
	{
		printf(STR_INVALID_EXT, argv[1]);
		return (FALSE);
	}
	if (!is_valid_file(argv[1]))
	{
		printf(STR_FILE_NOT_FOUND, argv[1]);
		return (FALSE);
	}
	if (!is_valid_map(argv[1]))
	{
		printf(STR_INVALID_MAP, argv[1]);
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

// TO DO: Ver substract como deve ser o arquivo .cub
// Ver se tem uma única linha para cada "type identifier" (R, NO, SO, WE, EA, S, F, C)
// Nâo mais que uma nem menos
// Ver se estes identifiers estão antes do mapa.
// Lembrar que podem haver tantos espaços quanto quiser antes e depois de cada linha
// Podem haver quantas linhas em branco quiser antes do mapa
// Verificar se o argumento que vem depois de cada identifier é válido
// Verificar se os arquivo .xpm são válidos (abrem corretamente, por exemplo)
// Verificar se as cores são válidas (números entre 0 e 255, não aceitar letras, se tem as virgulas, etc)
// Não deve havernas linhas mais nada além do identifier e seu argumento
// Não devem haver linhas com mais de 1 argumento ou com coisas aleátorias, (sem identifier por exemplo)
// MAPA
// Verificar se o mapa tem mapa
// Verificar se o mapa é válido. O que é um mapa válido?
// Acho que é só ir caracter por caracter
// ignora espaços até encontrar um 1 (se não encontrar, retorna erro) 
// depoisdo 1 deve haver apenas 0, N, S, E, W (Depois adicionaremos mais para portas (O e D) e sprites)
// até que encontre um 1 novamente seguido por um espaço ou ou \n
// Se encontrou o 1 e o \n em seguida a linha está ok
// Se encontrou o 1 e o espaço em seguida, verifica se há apenas espaços até o \n
// Essa verificação tem que fazer na horizontal e na vertical
// ver se colocou o player uma vez e não mais de uma vez
// Enfim tem uma lista de possíveis erros nos testes de repositórios por ai

static void	init_params(t_params *params)
{
	params->ceilcolor = -1;
	params->floorcolor = -1;
	params->east = NULL;
	params->north = NULL;
	params->south = NULL;
	params->west = NULL;
}

char	**fetch_map_array(int fd)
{
	char	*line;
	char	*tmp;
	char	**ret;

	if (fd == -1)
		return (NULL);
	tmp = ft_get_next_line(fd);
	while (ftex_is_in_set(*tmp, VALID_ID))
	{
		free(tmp);
		tmp = ft_get_next_line(fd);
		if (!tmp)
			return (NULL);
	}
	line = ft_strdup("");
	while (tmp)
	{
		line = ft_strmerge(line, tmp);
		tmp = ft_get_next_line(fd);
	}
	ret = ft_split(line, '\n');
	ret = insert_padding(ret, string_max_size(ret));
	close(fd);
	free(line);
	return (ret);
}

short int	is_valid_map(char *str)
{
	t_params params;

	init_params(&params);
}

short int	print_map(char *str)
{
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (TRUE);
}
