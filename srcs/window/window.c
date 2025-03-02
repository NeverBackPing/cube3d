/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:02:54 by gtraiman          #+#    #+#             */
/*   Updated: 2025/02/28 18:02:55 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"
#include <stdlib.h>

// Dessine un carré en dessinant pixel par pixel
void draw_square(t_vars *vars, int start_x, int start_y, int square_size, int color)
{
    int x;
    int y;

    y = start_y;
    while (y < start_y + square_size)
    {
        x = start_x;
        while (x < start_x + square_size)
        {
            mlx_pixel_put(vars->mlx, vars->win, x, y, color);
            x++;
        }
        y++;
    }
}

// Fonction appelée quand l'utilisateur clique sur la croix pour fermer la fenêtre
int close_window(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    // Si MLX sous Linux, pensez à détruire l'affichage avec mlx_destroy_display(vars->mlx);
    exit(0);
    return (0);
}

// Hook clavier pour gérer la touche Échap et les flèches directionnelles
int key_hook(int keycode, t_vars *vars)
{
    // Touche Échap (65307 sur Linux, 53 sur macOS)
    if (keycode == 65307)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    // Flèche gauche (65361) : déplace le carré de 10 pixels vers la gauche
    else if (keycode == 65361)
        vars->square_x -= 10;
    // Flèche haut (65362) : déplace le carré de 10 pixels vers le haut
    else if (keycode == 65362)
        vars->square_y -= 10;
    // Flèche droite (65363) : déplace le carré de 10 pixels vers la droite
    else if (keycode == 65363)
        vars->square_x += 10;
    // Flèche bas (65364) : déplace le carré de 10 pixels vers le bas
    else if (keycode == 65364)
        vars->square_y += 10;

    // Effacer la fenêtre et redessiner le carré à sa nouvelle position
    mlx_clear_window(vars->mlx, vars->win);
    draw_square(vars, vars->square_x, vars->square_y, 100, 0xFFFFFF);
    return (0);
}

// Initialise la fenêtre, définit la position initiale du carré et installe les hooks
int ft_window(void)
{
    t_vars vars;

    vars.mlx = mlx_init();
    if (!vars.mlx)
        return (1);

    vars.win = mlx_new_window(vars.mlx, 800, 600, "Cub3d Window");
    if (!vars.win)
    {
        free(vars.mlx);
        return (1);
    }

    // Position initiale du carré (par exemple, centré)
    vars.square_x = 350;
    vars.square_y = 250;

    // Dessiner le carré initial (100x100, blanc)
    draw_square(&vars, vars.square_x, vars.square_y, 100, 0xFFFFFF);

    // Installer le hook pour la fermeture via la croix
    mlx_hook(vars.win, 17, 0, (int (*)())close_window, &vars);
    // Installer le hook clavier pour gérer les touches (KeyPress = 2)
    mlx_hook(vars.win, 2, 1L<<0, (int (*)())key_hook, &vars);

    mlx_loop(vars.mlx);
    return (0);
}
