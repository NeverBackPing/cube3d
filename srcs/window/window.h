#ifndef WINDOW_H
# define WINDOW_H

# include <X11/X.h>
# include <X11/keysym.h>
# include "../../../mlx/mlx.h"
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include "../includes/main.h"


# define FOV 0.66

# define NEXTO0 "01NEWS"
# define NEXTO1 " 1"
# define PPLR "NEWS"
# define RADTURN 0.05
# define SCREENX 2000
# define SCREENY 1000
# define SPEED 0.1
# define COLOR 0xFF0000

int	ft_tablen(char **tab);
int close_window(t_env *env);
void ft_lim(t_ray *r, int lh, int *size_line, int *bpp, char *data, int x);
void ft_setdelta(t_ray *r);
void ft_draw(t_game *game, t_window *win);
t_vec    ft_move(t_vec *pos, t_vec *dir, t_game *game, int keycode);
void ft_setplan(t_player *plr, double planeLength);
void ft_initp(t_game *game, t_player *plr);
t_vec turnv(t_vec v, double rad);

#endif
