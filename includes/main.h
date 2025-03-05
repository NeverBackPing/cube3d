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
// # include "../srcs/window/window.h"


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
	int		width;
	int		height;
	int		lenght_index;
	char	**map;
} t_map;


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
   
   
   // Structure pour le joueur et la caméra
   typedef struct {
	   // Position du joueur dans le monde
	   t_vec pos;
	   
	   // Vecteur direction indiquant où regarde le joueurz
	   t_vec dir;
	   
	   // Vecteur du plan de la caméra (doit être perpendiculaire à la direction)
	   // La longueur de ce vecteur détermine le champ de vision (FOV)
	   t_vec plane;
   } t_player;
   
   
   // Structure pour le rayon, utilisé dans la phase DDA
   typedef struct {
	   // Vecteur direction du rayon pour une colonne donnée
	   t_vec rayDir;
	   
	   // Position actuelle dans la grille (case en cours)
	   int mapX;
	   int mapY;
	   
	   // Distance du point de départ à la première intersection avec un bord de cellule
	   double sideDistX;
	   double sideDistY;
	   
	   // Distance à parcourir pour passer d'un bord de cellule à l'autre sur l'axe X ou Y
	   double deltaDistX;
	   double deltaDistY;
	   
	   // Distance perpendiculaire du joueur au mur (utilisée pour corriger le fisheye)
	   double perpWallDist;
	   
	   // Indique la direction d'incrémentation dans la grille pour X et Y (valeurs -1 ou +1)
	   int stepX;
	   int stepY;
	   
	   // Flag indiquant si un mur a été touché (0 = non, 1 = oui)
	   int hit;
	   
	   // Indique quel côté du mur a été touché :
	   // 0 : côté vertical (mur NS) ; 1 : côté horizontal (mur EW)
	   int side;
   } t_ray;
   
typedef struct {
   
	   void* mlx;
	   int *win;
} t_window;

typedef struct s_game
{
	int screenWidth;   // largeur de l'écran (en pixels)
    int screenHeight;  // hauteur de l'écran (en pixels)
    
    // Variables de timing pour le calcul du frameTime et de l'FPS
    double time;
    double oldTime;
    double frameTime;
    
    // Structures essentielles
    t_player plr;
	char		*line_save;
	int			fd;
	t_map		map;
	t_texture	texture;
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
int		ft_window(t_game *game);

#endif