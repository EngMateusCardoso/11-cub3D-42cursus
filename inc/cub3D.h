/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:31:13 by matcardo          #+#    #+#             */
/*   Updated: 2023/09/07 15:42:27 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
// # include <math.h>

# define WIN_SIDE 500
# define MLX_ERROR 42

// Constants
# define TRUE 1
# define FALSE 0

// Window constants
# define WIN_WIDTH 500
# define WIN_HEIGHT 500

// Errors
# define STR_INVALID_ARG "Error\nUsage: ./cub3D <map.cub>\n"
# define STR_INVALID_MAP "Error\nInvalid map file: %s\n"

typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_win {
	void	*mlx_ptr;
	char	*win_ptr;
	t_img	img;
}				t_win;

short int	check_args(int argc, char **argv);

#endif
