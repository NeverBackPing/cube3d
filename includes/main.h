/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:14:37 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/05 15:14:37 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}	t_vec;


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
}	t_img;

/* -----------------------------------------------------
	Prototypes des fonctions MLX et hooks
	----------------------------------------------------- */


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
}	t_texture;

typedef struct s_map
{
	int		row;
	int		lenght;
	int		width;
	int		height;
	int		lenght_index;
	char	**map;
} t_map;

typedef struct {
	t_vec pos;
	t_vec dir;
	t_vec plane;
} t_player;



typedef struct {

	int	mapX;
	int	mapY;
	int	stepX;
	int	stepY;
	int	hit;
	int	color;
	int	side;
	t_vec rayDir;
	t_vec sideDist;
	t_vec deltaDist;
	double perpWallDist;

} t_ray;

typedef struct {

	void 	*img;
	void	*mlx;
	int		*win;
} t_window;


typedef struct s_game
{
    t_player plr;
	char		*line_save;
	int			fd;
	t_map		map;
	t_texture	texture;
} t_game;


typedef struct s_env {
    t_window    win;
    t_game      game;
    t_player    *plr;  // ou game.plr si tu préfères y accéder directement
    int		mouse;
} t_env;

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
int	ft_window(t_game *game);

#endif
