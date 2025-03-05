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



void ft_setplan(t_player *plr, double planeLength);
void ft_initp(t_game *game, t_player *plr);
t_vec turnv(t_vec v, double rad);

#endif
