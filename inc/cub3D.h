/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:31:13 by matcardo          #+#    #+#             */
/*   Updated: 2023/11/04 15:28:12 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// =============================================================================
// LIBRARIES
// =============================================================================

# include "../libraries/minilibx-linux/mlx.h"
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
# define WIN_WIDTH 640
# define WIN_HEIGHT 640
# define PLAYER_SIZE 20
# define MAX_MAP_SCALE 0.2

// Errors
# define STR_INVALID_ARG "Error\nUsage: ./cub3D <map.cub>\n"
# define STR_INVALID_EXT "Error\nInvalid file extension: %s\nUsage: ./cub3D <map.cub>\n"
# define STR_FILE_NOT_FOUND "Error\nFile not found: %s\n"
# define STR_INVALID_MAP "Error\nInvalid map in: %s\n"

// =============================================================================
// STRUCTURES
// =============================================================================

typedef struct s_raycaster {
	float	first_hit_x;
	float	first_hit_y;
	float	y_offset;
	float	x_offset;
	int		map_x;
	int		map_y;
}				t_raycaster;

typedef struct s_coord {
	int		x;
	int		y;
	float	len;
}				t_coord;

typedef struct s_map {
	char	**map;
	int		width;
	int		height;
	float	minimap_scale;
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
	int			endian;
	int			bpp;
	int			line_len;
	int			img_width;
	int			img_height;
	int			*data;
	int			ceiling_color;
	int			floor_color;
	t_player	player;
	t_map		map;
	int			textures[4][64][64];
}				t_img;

typedef struct s_win {
	void	*mlx_ptr;
	char	*win_ptr;
	t_img	img;
}				t_win;

// =============================================================================
// ENUMS
// =============================================================================

enum e_directions
{
	NO,
	SO,
	EA,
	WE
};

// =============================================================================
// PROTOTYPES
// =============================================================================

// main.c
int			main(int argc, char **argv);
int			init_game(char *file);
void		init_game_params(t_win *win, char *file);
int			start_window(t_win *win, char *file);
void		start_image(t_win *win);

// init_functions_1.c
void		init_map_dimensions(t_win *win, char *file);
void		init_map(t_win *win, char *file);
short int	is_map_line(char *line);
void		init_player_position(t_win *win, char *file);
void		init_player_position_line(t_win *win, char *line, int i);

// init_functions_2.c
void		init_roof_and_ceiling_color(t_win *win, char *file);
int			get_color_in_line(char *line);
void		init_textures(t_win *win, char *file);
void		get_texture(char *line, t_win *win, int direction);
char		*path_to_texture(char *line);

// check_args.c
short int	check_args(int argc, char **argv);
short int	is_valid_file_extension(char *str);
short int	is_valid_file(char *str);
short int	is_valid_map(char *str);

// hooks.c
int			handle_input(int keysys, t_win *win);
void		rotate_player(int keysys, t_win *win);
int			handle_mouse(int keysys, int x, int y, t_win *win);
int			close_window(t_win *win);
void		free_map(char **map);

// move_player.c
void		move_player(int keysys, t_win *win);
void		move_player_forward(t_win *win);
void		move_player_backward(t_win *win);
void		move_player_left(t_win *win);
void		move_player_right(t_win *win);

// working
void		print_screen(t_img *img);
void		raycasterr(t_img *img);
t_coord		get_horizontal_hit(t_img *img, float angle);
t_coord		get_vertical_hit(t_img *img, float angle);
void		render_line(t_img *img, float x0, float y0, float x1, float y1, int color, float step, float step_offset, float x_hit);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
float		dist_between_points(float x1, float y1, float x2, float y2);
void	render_map(t_img *img);
void	render_map_unit(t_img *img, int x, int y, int color);
void	render_player(t_img *img);
#endif
