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

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_wall
{
	char	*c;
	void	*p;
	int		height;
	int		width;
	void	*img;
	int		bpp;
	int		size_line;
	int		endian;
}	t_wall;

typedef struct s_texture
{
	int		r;
	int		g;
	int		b;
	int		count;
	int		count_player;
	t_wall	*n;
	t_wall	*s;
	t_wall	*e;
	t_wall	*w;
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
}	t_map;

typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_player;

typedef struct s_ray
{
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
	int			color;
	int			side;
	int			lh;
	int			ds;
	int			de;
	int			texx;
	int			texy;
	t_vec		raydir;
	t_vec		sidedist;
	t_vec		deltadist;
	t_wall		*texture;
	double		wallx;
	double		texpos;
	double		perpwalldist;

}	t_ray;

typedef struct s_minimap
{
	int	px;
	int	py;
	int	orientation_x;
	int	orientation_y;
	int	start_x;
	int	start_y;
}	t_minimap;

typedef struct s_window
{
	void		*img;
	void		*mlx;
	int			*win;
	int			bpp;
	int			size_line;
	t_minimap	minimap;
}	t_window;

typedef struct s_game
{
	t_player		plr;
	char			*line_save;
	int				fd;
	t_map			map;
	t_texture		txt;
}	t_game;

typedef struct s_env {
	t_window	win;
	t_game		game;
	t_player	*plr;
	int			mouse;
}	t_env;

// monitor/error.c
void	print_error(char *str);
// monitor/init_struct.c
// handler_fd.c
void	handler_fd(t_game *game, char	*fd);
void	init_struct(t_game *game);
void	free_ressource(t_game *game);
void	map_is_good(t_game *game);
void	edit_map(t_game *game);
void	alloc_map(t_game *game, t_map *map, int lengh, char *line);
void	get_map(t_game *game, char *filename);
bool	just_space(char *line);
void	start_cpy_map(t_game *game, t_map *map, char *line);
void	get_set_graph(t_game *game, char *filename);
void	check_sep(t_game *game, char *line);
void	check_fail(t_game *game);
bool	escape_sequences(char c);
void	set_fail(t_game *game);
void	alloc_graph_set(t_game *game, char *file_xpm, char *set_graph);
void	check_xpm(t_game *game, char *line, int start, int end);
void	check_is_fail(t_game *game, char *str);
int		find_index(char *line, char *str);
void	close_fd(t_game *game);
void	open_fd(t_game *game, char *filename);
void	check_rgb(t_game *game);
int		rgb_check(t_game *game, char *line, int i);
void	set_color(t_game *game, char *set);
void	map_init(t_game *game);
void	get_lenght_map(t_game *game);
void	draw_minimap(t_game *game, char *data, t_window *win, int size_line);
void	draw_tile(t_window *win, int *img_data, int color, int size_line);
void	ft_draw_background(t_game *game, char *data, int size_line);
int		ft_window(t_game *game);

#endif
