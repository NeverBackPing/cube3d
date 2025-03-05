#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include "checkmap.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include "../srcs/dependency/libft/libft.h"
# include "../srcs/dependency/gnl/get_next_line.h"

/* ----------------------------
   Structure pour un vecteur 3D
   ---------------------------- */
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
} t_vec;

/* Fonctions sur les vecteurs (définitions dans un autre fichier source) */
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_normalize(t_vec a);

/* ----------------------------
	Structure regroupant les paramètres de la scène
	---------------------------- */
typedef struct s_scene
{
	int		win_width;
	int		win_height;
	t_vec	camera;
	t_vec	view_center;
	t_vec	lower_left;
	double	vp_width;
	double	vp_height;
	t_vec	cube_min;
	t_vec	cube_max;
} t_scene;

/* ----------------------------
	Structure pour l'image
	---------------------------- */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

/* ----------------------------
	Structure pour (u,v)
	---------------------------- */
typedef struct s_uv
{
	double	u;
	double	v;
} t_uv;

typedef struct s_bounds
{
	double	tmin;
	double	tmax;
	double	tymin;
	double	tymax;
	double	tzmin;
	double	tzmax;
	double	temp;
} t_bounds;

/* -----------------------------------------------------
	Prototypes des fonctions MLX et hooks
	----------------------------------------------------- */
typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		square_x;
	int		square_y;
	t_scene	scene;
} t_vars;

typedef struct s_texture
{
	int		r;
	int		g;
	int		b;
	int		count;
	int		count_player;
	char	*north_texture;
	char	*east_texture;
	char	*south_texture;
	char	*west_texture;
	int		ground_color;
	char	*line_save;
	int		roof_color;
} t_texture;

typedef struct s_map
{
	int		row;
	int		lenght;
	int		lenght_index;
	char	**map;
} t_map;

typedef struct s_game
{
	char		*line_save;
	int			fd;
	t_map		map;
	t_texture	texture;
	t_vars		vars;
} t_game;

// monitor/init_struct.c
void	init_struct(t_game *game);
void	free_ressource(t_game *game);
// parsing/check_map.c
void	map_is_good(t_game *game);
// parsing/edit_map.c
void	edit_map(t_game *game);
// parsing/ft_get_map.c
void	alloc_map(t_game *game, t_map *map, int lengh, char *line);
bool	escape_sequences(char c);
void	get_map(t_game *game, char *filename);
bool	just_space(char *line);
void	start_cpy_map(t_game *game, t_map *map, char *line);
// parsing/graph.c
void	get_set_graph(t_game *game, char *filename);
// parsing/get_sprites.c
void	alloc_graph_set(t_game *game, char *file_xpm, char *set_graph);
void	check_xpm(t_game *game, char *line, int start, int end);
void	check_is_fail(t_game *game, char *str);
int		find_index(char *line, char *str);
// parsing/handler_fd.c
void	close_fd(t_game *game);
void	open_fd(t_game *game, char *filename);
// parsing/get_rgb.c
void	check_rgb(t_game *game);
int		rgb_check(t_game *game, char *line, int i);
void	set_color(t_game *game, char *set);
// parsing/map_tool.c
void	map_init(t_game *game);
void	get_lenght_map(t_game *game);

//window/window.c
/* -----------------------------------------------------
   Prototypes des fonctions de rendu
   ----------------------------------------------------- */
void	init_scene(t_scene *scene);
int		compute_pixel_color(int x, int y, t_scene *scene);
void	render_pixels(char *addr, int line_length, int bits_per_pixel, t_scene *scene);
void	render_scene(t_vars *vars);
int		close_window(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);
/* Prototype de la fonction d'intersection rayon-cube (AABB) */
int		ft_window(t_game *game, t_vars vars);
int		intersect_cube(t_vec origin, t_vec dir, t_vec box_min, t_vec box_max, double *t_out);
#endif
