/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:47:15 by gtraiman          #+#    #+#             */
/*   Updated: 2025/02/28 18:03:47 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WINDOW_H
# define WINDOW_H

# include <X11/X.h>
# include <X11/keysym.h>
# include "../../../mlx/mlx.h"
# include <mlx.h>

typedef struct s_vars
{
    void    *mlx;
    void    *win;
    int     square_x;
    int     square_y;
}   t_vars;

// Affiche un carré de taille square_size à la position (start_x, start_y) dans la couleur color
void    draw_square(t_vars *vars, int start_x, int start_y, int square_size, int color);

// Ferme la fenêtre proprement (hook pour la croix)
int     close_window(t_vars *vars);

// Hook clavier : gère la touche Échap et les flèches pour déplacer le carré
int     key_hook(int keycode, t_vars *vars);

// Lance la fenêtre MLX et initialise le dessin
int     ft_window(void);


#endif
