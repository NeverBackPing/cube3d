#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../dependency/libft/libft.h"
# include "../dependency/gnl/get_next_line.h"
# include "../srcs/parsing/checkmap.h"

typedef struct s_texture
{
	char	*north_texture;
	char	*east_texture;
	char	*south_texture;
	char	*west_texture;
	int		ground_color[3];
	int		roof_color[3];
} t_texture;

typedef struct s_map
{
	char	**map;
} t_map;

typedef struct s_game
{
	int			fd;
	t_map		map;
	t_texture	texture;
} t_game;

//parsing/ft_get_map.c
void	get_map(t_game *game, char *filename);
void	open_fd(t_game *game, char *filename);

#endif