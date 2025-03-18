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
# define TILE_SIZE 10
# define PLAYER_SIZE 4
# define MINIMAP_SCALE 0.2
# define MINIMAP_SIZE 150
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
// void ft_lim(t_ray *r, int lh, int *size_line, int *bpp, char *data, int x);
t_wall  *ft_get_texture(t_game *game, t_ray *r);
void	calculate_wallx(t_ray *r, t_player *plr);
void    calculate_texx(t_ray *r, int texWidth);
void    draw_textured_wall(t_ray *r, int x, char *data, t_window *win);
t_vec	ft_testpos(t_vec newpos, t_vec *pos, t_game *game);
void    ft_free_textures(t_game *game, t_window *win);
void    load_textures(t_env *env, t_game *game, t_window *win);
void    ft_init_ray(t_ray *r, t_game *game, int x);

void    ft_allcol(t_game *game, char *data, t_window *win);
void    ft_setdelta(t_ray *r);
void    ft_draw(t_game *game, t_window *win);
t_vec   ft_move(t_vec *pos, t_vec *dir, t_game *game, int keycode);
void    ft_setplan(t_player *plr, double planeLength);
void    ft_initp(t_game *game, t_player *plr);
t_vec   turnv(t_vec v, double rad);

#endif
