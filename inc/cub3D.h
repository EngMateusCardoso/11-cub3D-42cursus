/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:31:13 by matcardo          #+#    #+#             */
/*   Updated: 2023/09/29 16:20:05 by matcardo         ###   ########.fr       */
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

// Window constants
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
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
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
int			init_game(void);

// check_args.c
short int	check_args(int argc, char **argv);
short int	is_valid_file_extension(char *str);
short int	is_valid_file(char *str);
short int	is_valid_map(char *str);

int			handle_input(int keysys, t_win *win);
void		start_image(t_win *win);

#endif
