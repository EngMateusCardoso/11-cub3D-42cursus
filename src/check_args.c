/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:16:04 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/10 15:44:46 by thabeck-         ###   ########.fr       */
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

short int	print_error(char *error, char *param, char *set)
{
	if (set && param)
		printf(error, param, set);
	else if(set)
		printf(error, set);
	else if (param)
		printf(error, param);
	else
		printf("%s", error);
	return (FALSE);
}

short int	print_error_char(char *error, char param)
{
	if (param)
		printf(error, param);
	else
		printf("%s", error);
	return (FALSE);
}

static int	istrimmed(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (TRUE);
		set++;
	}
	return (FALSE);
}

static int	strsize(char *str, char *set)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (!istrimmed(*str++, set))
			i++;
	}
	return (i);
}

char	*ftex_strerase(char *str, char *set)
{
	size_t	size;
	char	*res;

	if (!str)
		return (NULL);
	size = strsize(str, set);
	res = (char *)malloc(sizeof(char) * size + 1);
	while (*str)
	{
		if (!istrimmed(*str, set))
			*res++ = *str++;
		else
			str++;
	}
	*res = '\0';
	return (res - size);
}

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

static int	is_in_del(char c, char *del)
{
	int	i;

	i = -1;
	while (del[++i])
	{
		if (c == del[i])
			return (i);
	}
	return (-1);
}

static char	find_new(char *ret, int index)
{
	int	len;

	len = ft_strlen(ret);
	if (index > len - 1)
		return (ret[len - 1]);
	else
		return (ret[index]);
}

void	ftex_tr(char *str, char *del, char *replace)
{
	int		index;
	int		i;

	if (!str || !del || !replace)
		return ;
	i = -1;
	while (str[++i])
	{
		index = is_in_del(str[i], del);
		if (index == -1)
			continue ;
		str[i] = find_new(replace, index);
	}
}

void	tr_matrix(char **matrix, char *del, char *replace)
{
	int	i;

	i = -1;
	while (matrix[++i])
		ftex_tr(matrix[i], del, replace);
}

void	print_color_map(char **map)
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
				printf("\e[1;91m%c\e[0m", map[i][j]);
			else if (map[i][j] == '0')
				printf("\e[1;94m%c\e[0m", map[i][j]);
			else if (ftex_is_in_set(map[i][j], "NSEW"))
				printf("\e[1;92m%c\e[0m", map[i][j]);
			else if (map[i][j] == ' ' || map[i][j] == '\t')
				printf("%c", ' ');
			else
				printf("\e[1;93m%c\e[0m", map[i][j]);
		}
		printf("\n");
		j = -1;
	}
}

int	comma_counter(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}

int	get_color(int r, int g, int b)
{
	int	rgb;

	rgb = 0;
	rgb += (r & 0xFF) << 16;
	rgb += (g & 0XFF) << 8;
	rgb += (b & 0XFF);
	return (rgb);
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

short int	is_str_number(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (FALSE);
			j++;
		}
		i++;
		j = 0;
	}
	return (TRUE);	
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

short int	validate_texture_file(char *param, char *file, char **store)
{
	int		fd;
	char	*dot;

	if (*store)
		return (print_error(STR_DUPLICATED_TEXTURE, param, NULL));
	if (!file)
		return (FALSE);
	dot = ft_strrchr(file, '.');
	if (!dot || ft_strncmp(dot, ".xpm\n", 5))
		return (print_error(STR_INCORRECT_TEXTURE, param, file));
	file[ft_strlen(file) - 1] = '\0';
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(STR_TEXTURE_NOT_FOUND, param, file));
	close(fd);
	*store = ft_strdup(file);
	return (TRUE);
}

void	gnl_purge(char *tmp, int fd)
{
	if (fd == -1)
		return ;
	free(tmp);
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	close (fd);
}

short int	check_parameter_matrix(t_params *params, char **matrix, char *file, char *tmp)
{
	short int	valid;

	valid = FALSE;
	matrix = ft_split(tmp, ' ');
	matrix[1] = join_color_set(matrix);
	if (!ft_strncmp(matrix[0], "NO", 2) && ft_strlen(matrix[0]) == 2)
		valid = validate_texture_file(matrix[0], matrix[1], &params->north);
	else if (!ft_strncmp(matrix[0], "SO", 2) && ft_strlen(matrix[0]) == 2)
		valid = validate_texture_file(matrix[0], matrix[1], &params->south);
	else if (!ft_strncmp(matrix[0], "EA", 2) && ft_strlen(matrix[0]) == 2)
		valid = validate_texture_file(matrix[0], matrix[1], &params->east);
	else if (!ft_strncmp(matrix[0], "WE", 2) && ft_strlen(matrix[0]) == 2)
		valid = validate_texture_file(matrix[0], matrix[1], &params->west);
	else if (!ft_strncmp(matrix[0], "F", 1) && ft_strlen(matrix[0]) == 1)
		valid = validate_color_set(matrix[0], matrix[1], &params->floor_color);
	else if (!ft_strncmp(matrix[0], "C", 1) && ft_strlen(matrix[0]) == 1)
		valid = validate_color_set(matrix[0], matrix[1], &params->ceil_color);
	else
		print_error(STR_INVALID_ID_MAP, matrix[0], file);
	free_map(matrix);
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
	if(!ftex_is_in_set((params->dev_map)[0][0], VALID_GLOBAL_ID))
		return (print_error(STR_INVALID_ID_MAP, (params->dev_map)[0], NULL));
	if (params->north == NULL)
		return (print_error(STR_NO_TEXTURE, "NO", NULL));
	if (params->east == NULL)
		return (print_error(STR_NO_TEXTURE, "EA", NULL));
	if (params->south == NULL)
		return (print_error(STR_NO_TEXTURE, "SO", NULL));
	if (params->west == NULL)
		return (print_error(STR_NO_TEXTURE, "WE", NULL));
	if (params->ceil_color == -1)
		return (print_error(STR_NO_COLOR, "C", NULL));
	if (params->floor_color == -1)
		return (print_error(STR_NO_COLOR, "F", NULL));
	return (TRUE);
}

short int	files_validation(t_params *params, char *file)
{
	int		fd;
	char	*tmp;
	char	**parameters;
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

static void	init_params(t_params *params)
{
	params->ceil_color = -1;
	params->floor_color = -1;
	params->east = NULL;
	params->north = NULL;
	params->south = NULL;
	params->west = NULL;
}

void	free_params_validation(t_params *params)
{
	free_map(params->map);
	free_map(params->dev_map);
	free(params->north);
	free(params->south);
	free(params->west);
	free(params->east);
}

short int	map_validation_failed(t_params *params)
{
	free_map(params->map);
	free_map(params->dev_map);
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

short int	count_player(char **map)
{
	int	i;
	int	j;
	int	player_char;

	i = -1;
	j = -1;
	player_char = 0;
	while (map[++i])
	{
		while (map[i][++j])
			if (ftex_is_in_set(map[i][j], VALID_PLAYER))
				player_char++;
		j = -1;
	}
	return (player_char);
}

short int	char_is_next_to(char **map, int x, int y, char c)
{
	if ((x > 0 && y > 0 && map[x - 1][y - 1] == c)
	|| (y > 0 && map[x][y - 1] == c)
	|| (map[x + 1] && y > 0 && map[x + 1][y - 1] == c)
	|| (x > 0 && map[x - 1][y] == c)
	|| (map[x + 1] && map[x + 1][y] == c)
	|| (x > 0 && map[x - 1][y + 1] == c)
	|| map[x][y + 1] == c
	|| (map[x + 1] && map[x + 1][y + 1] == c))
		return (TRUE);
	return (FALSE);
}

void	clear_around_map(char **map)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '1' && !char_is_next_to(map, i, j, '0')
			&& (!char_is_next_to(map, i, j, 'E')
			&& !char_is_next_to(map, i, j, 'W')
			&& !char_is_next_to(map, i, j, 'S')
			&& !char_is_next_to(map, i, j, 'N')))
				map[i][j] = ' ';
		}
		j = -1;
	}
}

char	validate_map_chars(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
			if (!ftex_is_in_set(map[i][j], VALID_MAP_CHARS))
				return (map[i][j]);
		j = -1;
	}
	return ('\0');
}

short int	is_border(char **map, int x, int y, char c)
{
	if (x == 0 || y == 0 || map[x][y + 1] == '\0' || map[x + 1] == NULL)
		return (TRUE);
	if (map[x - 1][y - 1] == c
	|| map[x][y - 1] == c
	|| map[x + 1][y - 1] == c
	|| map[x - 1][y] == c
	|| map[x + 1][y] == c
	|| map[x - 1][y + 1] == c
	|| map[x][y + 1] == c
	|| map[x + 1][y + 1] == c)
		return (TRUE);
	return (FALSE);
}

void	outline_walls(char **map)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (map[++x])
	{
		while (map[x][++y])
			if (map[x][y] == '1')
				if (is_border(map, x, y, ' '))
					map[x][y] = '9';
		y = -1;
	}
}

void	outline_useless_walls(char **map)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (map[++x])
	{
		while (map[x][++y])
			if (map[x][y] == '!')
				if (!is_border(map, x, y, '0')
					&& !is_border(map, x, y, '1'))
					map[x][y] = '#';
		y = -1;
	}
}

short int	forked_polygon(char **map, int x, int y)
{
	int	i;

	i = 0;
	if (map[x][y + 1] == '9')
		i++;
	if (y > 0 && map[x][y - 1] == '9')
		i++;
	if (map[x + 1] && map[x + 1][y] == '9')
		i++;
	if (x > 0 && map[x - 1][y] == '9')
		i++;
	if (i < 2)
		return (FALSE);
	return (TRUE);
}

int	check_end(char **map, int x, int y, char c)
{
	return ((y > 0 && map[x][y + 1] == c && map[x][y - 1] == c)
	|| (x > 0 && map[x + 1] && map[x + 1][y] == c && map[x - 1][y] == c)
	|| (x > 0 && map[x - 1][y] == c && map[x][y + 1] == c)
	|| (x > 0 && y > 0 && map[x][y - 1] == c && map[x - 1][y] == c)
	|| (y > 0 && map[x + 1] && map[x + 1][y] == c && map[x][y - 1] == c)
	|| (map[x + 1] && map[x + 1][y] == c && map[x][y + 1] == c));
}

short int	recursive_polygon(char **map, int x, int y);

short int	slide_polygon(char **map, int x, int y, char fill)
{
	while (1)
	{
		if (map[x + 1] && map[x + 1][y] == '9')
			map[x++][y] = fill;
		else if (y > 0 && map[x][y - 1] == '9')
			map[x][y--] = fill;
		else if (x > 0 && map[x - 1][y] == '9')
			map[x--][y] = fill;
		else if (map[x][y + 1] == '9')
			map[x][y++] = fill;
		else if (check_end(map, x, y, fill))
		{
			map[x][y] = fill;
			return (TRUE);
		}
		else
			return (FALSE);
		if (forked_polygon(map, x, y))
		{
			if (recursive_polygon(map, x, y))
				return (TRUE);
		}
	}
}

short int	recursive_polygon(char **map, int x, int y)
{
	if (map[x + 1] && map[x + 1][y] == '9')
		return (slide_polygon(map, x + 1, y, '!'));
	if (y > 0 && map[x][y - 1] == '9')
		return (slide_polygon(map, x, y - 1, '!'));
	if (x > 0 && map[x - 1][y] == '9')
		return (slide_polygon(map, x - 1, y, '!'));
	if (map[x][y + 1] == '9')
		return (slide_polygon(map, x, y + 1, '!'));
	return (FALSE);
}

t_xy	get_player_position(char **map, int x, int y)
{
	t_xy	xy;

	xy.x = x - 1;
	xy.y = y - 1;
	while (map[++xy.x])
	{
		while (map[xy.x][++xy.y])
			if (ftex_is_in_set(map[xy.x][xy.y], VALID_PLAYER))
				break ;
		if (ftex_is_in_set(map[xy.x][xy.y], VALID_PLAYER))
			break ;
		xy.y = -1;
	}
	if (xy.y == -1)
		xy.y++;
	return (xy);
}

short int	is_player_inside(char **map, int i, int j)
{
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '!')
			{
				while (map[i][j] && map[i][++j] == '!')
					continue ;
				if (ft_strchr(&map[i][j], '!'))
				{
					while (map[i][j] != '!')
					{
						if (ftex_is_in_set(map[i][j], VALID_PLAYER))
							return (TRUE);
						j++;
					}
				}
			}
			if (!map[i][j])
				j--;
		}
		j = -1;
	}
	return (FALSE);
}

short int	player_out_of_map(char **map)
{
	t_xy	xy;

	xy = get_player_position(map, 0, 0);
	if(map[xy.x - 1][xy.y] && map[xy.x][xy.y - 1] \
		&& map[xy.x + 1][xy.y] && map[xy.x][xy.y + 1] \
		&& (map[xy.x - 1][xy.y] == ' ' || map[xy.x - 1][xy.y] == '\t'
		|| map[xy.x + 1][xy.y] == ' ' || map[xy.x + 1][xy.y] == '\t'
		|| map[xy.x][xy.y - 1] == ' ' || map[xy.x][xy.y - 1] == '\t'
		|| map[xy.x][xy.y + 1] == ' ' || map[xy.x][xy.y + 1] == '\t'))
			return (TRUE);
	return (FALSE);
}

short int	walls_are_closed(char **map)
{
	t_xy	xy;
	short int	boolean;

	boolean = TRUE;
	xy = get_player_position(map, 0, 0);
	if (xy.x == 0 || map[xy.x][xy.y + 1] == '\0')
		return (FALSE);
	while (map[xy.x][xy.y] && map[xy.x][xy.y] != '9')
		xy.y++;
	while (boolean)
	{
		boolean = slide_polygon(map, xy.x, xy.y, '!');
		while (!is_player_inside(map, -1, -1))
		{
			tr_matrix(map, "!", "@");
			xy = get_player_position(map, 0, 0);
			if (xy.x == 0 || !ft_strchr(&map[xy.x][xy.y], '9'))
				return (FALSE);
			while (map[xy.x][xy.y] && map[xy.x][xy.y] != '9')
				xy.y++;
			boolean = slide_polygon(map, xy.x, xy.y, '!');
		}
		return (boolean);
	}
	return (FALSE);
}

void	remove_out_characters(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j] && map[i][j] != '!')
			map[i][j] = ' ';
		j = ft_strlen(map[i]);
		while (--j >= 0 && map[i][j] != '!')
			map[i][j] = ' ';
		j = -1;
	}
}

short int	inner_polygons_are_closed(char **map)
{
	char	*inner_wall;
	int		i;

	i = -1;
	while (map[++i])
	{
		inner_wall = ft_strchr(map[i], '9');
		if (inner_wall)
		{
			if (!slide_polygon(map, i, inner_wall - map[i], '@'))
				return (FALSE);
			i--;
		}
	}
	return (TRUE);
}

short int	map_validation(char **map)
{
	short int	player;
	char		invalid;

	player = count_player(map);
	if (player < 1)
		return (print_error(STR_PLAYER_NOT_FOUND, NULL, NULL));
	else if (player > 1)
		return (print_error(STR_MULTI_PLAYER, NULL, NULL));
	clear_around_map(map);
	invalid = validate_map_chars(map);
	if (invalid)
		return (print_error_char(STR_INVALID_MAP_CHAR, invalid));
	outline_walls(map);
	outline_useless_walls(map);
	if (!walls_are_closed(map))
		return (print_error(STR_MAP_WALLS_OPEN1, NULL, NULL));
	remove_out_characters(map);
	if (!inner_polygons_are_closed(map))
		return (print_error(STR_MAP_WALLS_OPEN2, NULL, NULL));
	if (player_out_of_map(map))
		return (print_error(STR_PLAYER_OUT, NULL, NULL));
	tr_matrix(map, "@", "1");
	tr_matrix(map, "!", "1");
	return (TRUE);
}

short int	is_valid_map(char *str)
{
	t_params params;

	init_params(&params);
	params.map = trim_map_array(open(str, O_RDONLY));
	params.dev_map = trim_map_array(open(str, O_RDONLY));
	if (!params.map)
		return (print_error(STR_EMPTY_MAP, NULL, NULL));
	if (!files_validation(&params, str))
		return (map_validation_failed(&params));
	if (!map_validation(params.map))
		return (map_validation_failed(&params));
	print_color_map(params.map);
	free_params_validation(&params);
	return (TRUE);
}
