/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:31:13 by matcardo          #+#    #+#             */
/*   Updated: 2024/01/03 20:37:13 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// =============================================================================
// LIBRARIES
// =============================================================================

# include "/usr/local/include/mlx.h"
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
# define WIN_TITLE "Cats vs Cucumbers"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 960

// Game constants
# define CUBE_SIZE 128
# define BASE_CUBE 7
# define PLAYER_SIZE 20
# define MAX_MAP_SCALE 0.2
# define PLAYER_MINIMAP_COLOR 0x00FF0000
# define WALL_MINIMAP_COLOR 0x00FFFFFF
# define ANGLE_OF_VIEW 60
# define RAYCASTER_NUM_RAYS 640

// Variables
# define VALID_ID "NSEWCF\n"
# define VALID_GLOBAL_ID "NSEWCF \t01\n"
# define VALID_MAP_CHARS "01 NSEW\n"
# define VALID_PLAYER "NSEW"
# define VALID_MAP "01"

// Errors
# define E_ARG "Error\nInvalid number of arguments\nUsage: ./cub3D <map.cub>\n"
# define E_EXT "Error\nInvalid file extension: %s\nUsage: ./cub3D <map.cub>\n"
# define E_FILE_404 "Error\nFile not found: %s\n"
# define E_INVMAP "Error\nInvalid map in: %s\n"
# define E_EMPTMAP "Error\nInvalid map\nThe map is empty\n"
# define E_INVID "Error\nInvalid map\nInvalid identifier: %s\n"
# define E_NOTEX "Error\nInvalid map\nMissing / Misplaced texture: '%s'\n"
# define E_DUPTEX "Error\nInvalid map\nDuplicated texture identifier: '%s'\n"
# define E_EXTTEX "Error\nInvalid map\nTexture file is not a .xpm: %s %s"
# define E_TEX_404 "Error\nInvalid map\nTexture file not found: %s %s\n"
# define E_NOCOLOR "Error\nInvalid map\nMissing / Misplaced color: '%s'\n"
# define E_RANGECOLOR "Error\nInvalid map\nRGB color out of range: %s %s"
# define E_RGBCOLOR "Error\nInvalid map\nWrong number of RGB colors: %s %s"
# define E_NOTNUMCOLOR "Error\nInvalid map\nRGB color is not numeric: %s %s"
# define E_DUPCOLOR "Error\nInvalid map\nDuplicate color identifier: '%s'\n"
# define E_PLAYER_404 "Error\nInvalid map\nPlayer not found in map\n"
# define E_MULTIPLAYER "Error\nInvalid map\nMultiple Players in map\n"
# define E_PLAYEROUT "Error\nInvalid map\nPlayer out of map\n"
# define E_MAPCHAR "Error\nInvalid map\nInvalid char in the map: '%c'\n"
# define E_MAPWALLS1 "Error\nInvalid map\nExternal walls are open\n"
# define E_MAPWALLS2 "Error\nInvalid map\nInternal walls are open\n"

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

typedef struct s_ray {
	int		wall_direction;
	float	angle;
	float	dist;
	float	x_hit;
}				t_ray;

typedef struct s_wall_vert_pxl {
	float	line_height;
	float	line_offset;
	float	step;
	float	step_offset;
	int		ray_pixel;
}				t_wall_vert_pxl;

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
	int			**textures[4];
	int			texture_width[4];
	int			texture_height[4];
}				t_img;

typedef struct s_win {
	void	*mlx_ptr;
	char	*win_ptr;
	t_img	img;
}				t_win;

typedef struct s_params
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		ceil_color;
	int		floor_color;
	char	**map;
	char	**dev_map;
}	t_params;

typedef struct s_xy
{
	int	x;
	int	y;
}	t_xy;

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

// init_map_functions.c
void		init_map_dimensions(t_win *win, char *file);
void		init_map(t_win *win, char *file);
void		init_map_scale(t_win *win);
short int	is_map_line(char *line);

// init_player_and_bg_functions.c
void		init_roof_and_ceiling_color(t_win *win, char *file);
int			get_color_in_line(char *line);
void		init_player_position(t_win *win, char *file);
void		init_player_position_line(t_win *win, char *line, int i);

// init_texture_functions.c
void		init_textures(t_win *win, char *file);
void		get_texture(char *line, t_win *win, int direction);
char		*path_to_texture(char *line);
void		set_texture(t_win *win, t_img img, int direction);

// check_args.c
short int	check_args(int argc, char **argv);
short int	is_valid_file_extension(char *str);
short int	is_valid_file(char *str);
short int	is_valid_map(char *str);

//check_args_utils.c
short int	print_error(char *error, char *param, char *set);
short int	print_error_char(char *error, char param);
int			istrimmed(char c, char const *set);
int			strsize(char *str, char *set);

//ftex_utils.c
int			is_in_del(char c, char *del);
char		find_new(char *ret, int index);
char		*ftex_strerase(char *str, char *set);
short int	ftex_is_in_set(char c, char *set);
void		ftex_tr(char *str, char *del, char *replace);

//map_validation.c
short int	count_player(char **map);
short int	char_is_next_to(char **map, int x, int y, char c);
void		clear_around_map(char **map);
char		validate_map_chars(char **map);
short int	map_validation(char **map);

//map_validation_utils.c
short int	is_border(char **map, int x, int y, char c);
void		outline_walls(char **map);
void		outline_useless_walls(char **map);
void		remove_out_characters(char **map);
short int	player_out_of_map(char **map);

//map_walls_validation.c
short int	is_player_inside(char **map, int i, int j);
short int	slide_polygon(char **map, int x, int y, char fill);
short int	recursive_polygon(char **map, int x, int y);
short int	forked_polygon(char **map, int x, int y);
short int	walls_are_closed(char **map);

//map_walls_validation_utils.c
int			check_end(char **map, int x, int y, char c);
t_xy		get_player_position(char **map, int x, int y);
short int	inner_polygons_are_closed(char **map);

//parameter_validation_1.c
short int	check_parameter_matrix(t_params *p, char **m, char *f, char *t);
short int	is_first_char_invalid(int fd, char **tmp);
short int	check_all_params(t_params *params);
short int	validate_texture_file(char *param, char *file, char **store);
short int	files_validation(t_params *params, char *file);

//parameter_validation_2.c
void		tr_matrix(char **matrix, char *del, char *replace);
char		*join_color_set(char **matrix);
short int	validate_color_set(char *param, char *set, int *store);

//parameter_utils.c
void		init_params(t_params *params);
void		free_params_validation(t_params *params);
short int	map_validation_failed(t_params *params);

//trim_map.c
char		**set_padding(char **matrix, int maxsize);
char		**trim_map_array(int fd);

//validation_utils.c
int			comma_counter(char *str);
int			get_color(int r, int g, int b);
short int	is_str_number(char **str);
void		gnl_purge(char *tmp, int fd);
int			str_maxsize(char **matrix);

// hooks.c
int			handle_input(int keysys, t_win *win);
void		rotate_player(int keysys, t_win *win);
int			close_window(t_win *win);
void		free_textures(int	**textures);
void		free_map(char **map);

// move_player.c
void		move_player(int keysys, t_win *win);
void		move_player_forward(t_win *win);
void		move_player_backward(t_win *win);
void		move_player_left(t_win *win);
void		move_player_right(t_win *win);

// print_creen.c
void		print_screen(t_img *img);
void		print_screen_background(t_img *img);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);

// raycaster.c
void		raycaster(t_img *img);
float		fix_angle(float angle);
t_ray		get_ray(t_img *img, t_coord hor_hit, t_coord vert_hit, t_ray ray);
t_ray		fix_fish_eye(t_ray ray, float angle);

// horizontal_hit.c
t_coord		get_horizontal_hit(t_img *img, float angle);
t_raycaster	get_horizontal_hit_ray(t_img *img, float angle);
void		horizontal_hit_ray_update(t_img *img, t_raycaster *ray, int *i);
float		dist_between_points(float x1, float y1, float x2, float y2);

// vertical_hit.c
t_coord		get_vertical_hit(t_img *img, float angle);
t_raycaster	get_vertical_hit_ray(t_img *img, float angle);
void		vertical_hit_ray_update(t_img *img, t_raycaster *ray, int *i);

// draw_walls.c
void		draw_walls(t_img *img, t_ray ray, int ray_index);
void		draw_wall_column(t_img *img, t_ray ray, \
	t_wall_vert_pxl wall_params, int ray_i);

#endif
