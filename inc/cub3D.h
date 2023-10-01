/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:31:13 by matcardo          #+#    #+#             */
/*   Updated: 2023/10/01 02:17:41 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// =============================================================================
// LIBRARIES
// =============================================================================

# include "../minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"
# include <unistd.h>	// write (?)
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free, exit
# include <fcntl.h>		// open, close, read
# include <math.h>

// =============================================================================
// CONSTANTS
// =============================================================================

// General constants
# define TRUE 1
# define FALSE 0

// Math constants
# define PI	3.141592
# define DR	0.0174533

# define MLX_ERROR 42

// Keys
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

// Window constants
# define CUBE_SIZE 64
# define BASE_CUBE 6
# define WIN_TITLE "Cats vs Cucumbers"
# define WIN_WIDTH 1500
# define WIN_HEIGHT 600

// Errors
# define STR_INVALID_ARG "Error\nUsage: ./cub3D <map.cub>\n"
# define STR_INVALID_EXT "Error\nInvalid file extension: %s\nUsage: ./cub3D <map.cub>\n"
# define STR_FILE_NOT_FOUND "Error\nFile not found: %s\n"
# define STR_INVALID_MAP "Error\nInvalid map in: %s\n"

// =============================================================================
// STRUCTURES
// =============================================================================

typedef struct s_raycaster {
	float	angle;
	float	first_hit_x;
	float	first_hit_y;
	float	y_offset;
	float	x_offset;
	int		r;
	int		map_x;
	int		map_y;
	int		mp;
	int		dof;
}				t_raycaster;

typedef struct s_map {
	char	**map;
	int		width;
	int		height;
}				t_map;

typedef struct player {
	float	x;
	float	y;
	float	cos;
	float	sin;
	float	angle;
}				t_player;


typedef struct s_img {
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_player	player;
	t_map		map;
}				t_img;

typedef struct s_win {
	void	*mlx_ptr;
	char	*win_ptr;
	t_img	img;
}				t_win;

// =============================================================================
// PROTOTYPES
// =============================================================================

// main.c
int			main(int argc, char **argv);
int			init_game(char *file);
void		init_game_params(t_win *win, char *file);
void		init_map(t_win *win, char *file);
short int	is_map(char *line);
void		init_map_dimensions(t_win *win, char *file);
void		init_player_position(t_win *win, char *file);
void		init_player_position_line(t_win *win, char *line, int i);

// check_args.c
short int	check_args(int argc, char **argv);
short int	is_valid_file_extension(char *str);
short int	is_valid_file(char *str);
short int	is_valid_map(char *str);

int			handle_input(int keysys, t_win *win);
void		start_image(t_win *win);
int			close_window(void);

#endif
