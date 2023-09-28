/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:31:13 by matcardo          #+#    #+#             */
/*   Updated: 2023/09/27 16:17:21 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define MLX_ERROR 42

// Constants
# define TRUE 1
# define FALSE 0
# define PI	3.141592
# define DR	0.0174533

// Window constants
# define WIN_WIDTH 1500
# define WIN_HEIGHT 600

// Errors
# define STR_INVALID_ARG "Error\nUsage: ./cub3D <map.cub>\n"
# define STR_INVALID_MAP "Error\nInvalid map file: %s\n"

typedef struct s_raytrace {
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
}				t_raytrace;

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

short int	check_args(int argc, char **argv);
int			handle_input(int keysys, t_win *win);
void		start_image(t_win *win);
#endif
