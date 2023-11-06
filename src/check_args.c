/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:16:04 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/06 01:59:32 by thabeck-         ###   ########.fr       */
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

short int	ftex_is_in_set(char c, char *set)
{
	if (!set)
		return (FALSE);
	while (*set)
	{
		if (c == *set)
			return (TRUE);
		set++;
	}
	return (FALSE);
}

void	print_colored_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				printf("\e[41m%c\e[0m", map[i][j]);
			else if (map[i][j] == '0')
				printf("\e[44m%c\e[0m", map[i][j]);
			else if (ftex_is_in_set(map[i][j], "NSEW"))
				printf("\e[42m%c\e[0m", map[i][j]);
			else if (map[i][j] == ' ')
				printf("%c", ' ');
			else
				printf("\e[46m%c\e[0m", map[i][j]);
		}
		printf("\n");
		j = -1;
	}
}

static void	init_params(t_params *params)
{
	params->ceilcolor = -1;
	params->floorcolor = -1;
	params->east = NULL;
	params->north = NULL;
	params->south = NULL;
	params->west = NULL;
}

short int	map_validation_failed(t_params *params, char **map)
{
	if (map)
		print_colored_map(map);
	free_map(map);
	free(params->north);
	free(params->south);
	free(params->west);
	free(params->east);
	return (FALSE);
}

static char	**set_padding(char **matrix, int maxsize)
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
static int	str_maxsize(char **matrix)
{
	int	i;
	int	size;
	int	maxsize;

	maxsize = 0;
	i = -1;
	while (matrix[++i])
	{
		size = ft_strlen(matrix[i]);
		if (size > maxsize)
			maxsize = size;
	}
	return (maxsize);
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

short int	is_valid_map(char *str)
{
	t_params params;

	init_params(&params);
	params.map = trim_map_array(open(str, O_RDONLY));
	if (!params.map)
	{
		printf(STR_EMPTY_MAP);
		return (FALSE);
	}
	print_colored_map(params.map);
	return (TRUE);
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
