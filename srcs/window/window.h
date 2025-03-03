#ifndef WINDOW_H
# define WINDOW_H

# include <X11/X.h>
# include <X11/keysym.h>
# include "../../../mlx/mlx.h"
# include <mlx.h>
# include <stdlib.h>
# include <math.h>

/* ----------------------------
   Structure pour un vecteur 3D
   ---------------------------- */
typedef struct s_vec
{
    double  x;
    double  y;
    double  z;
} t_vec;

/* Fonctions sur les vecteurs (définitions dans un autre fichier source) */
t_vec   vec_sub(t_vec a, t_vec b);
t_vec   vec_normalize(t_vec a);

/* ----------------------------
   Structure regroupant les paramètres de la scène
   ---------------------------- */
typedef struct s_scene
{
    int     win_width;
    int     win_height;
    t_vec   camera;
    t_vec   view_center;
    t_vec   lower_left;
    double  vp_width;
    double  vp_height;
    t_vec   cube_min;
    t_vec   cube_max;
} t_scene;

/* ----------------------------
   Structure pour l'image
   ---------------------------- */
typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_img;

/* ----------------------------
   Structure pour (u,v)
   ---------------------------- */
typedef struct s_uv
{
    double  u;
    double  v;
} t_uv;

typedef struct s_bounds
{
    double  tmin;
    double  tmax;
    double  tymin;
    double  tymax;
    double  tzmin;
    double  tzmax;
    double  temp;
} t_bounds;


/* -----------------------------------------------------
   Prototypes des fonctions MLX et hooks
   ----------------------------------------------------- */
typedef struct s_vars
{
    void    *mlx;
    void    *win;
    int     square_x;
    int     square_y;
    t_scene scene;
} t_vars;

/* -----------------------------------------------------
   Prototypes des fonctions de rendu
   ----------------------------------------------------- */
void    init_scene(t_scene *scene);
int     compute_pixel_color(int x, int y, t_scene *scene);
void    render_pixels(char *addr, int line_length, int bits_per_pixel, t_scene *scene);
void    render_scene(t_vars *vars);


void    draw_square(t_vars *vars, int start_x, int start_y, int square_size, int color);
int     close_window(t_vars *vars);
int     key_hook(int keycode, t_vars *vars);
int     ft_window(void);

/* Prototype de la fonction d'intersection rayon-cube (AABB) */
int     intersect_cube(t_vec origin, t_vec dir, t_vec box_min, t_vec box_max, double *t_out);

#endif
