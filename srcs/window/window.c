/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:30:00 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/07 00:00:52 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"

int	close_window(t_env *env)
{
	ft_free_textures(&env->game, &env->win);
	free_ressource(&env->game);
	mlx_destroy_window(env->win.mlx, env->win.win);
	mlx_destroy_display(env->win.mlx);
	free(env->win.mlx);
	exit(0);
	return (0);
}

void	load_textures(t_env *env, t_game *game, t_window *win)
{
	game->txt.n->img = mlx_xpm_file_to_image(win->mlx, game->txt.n->c,
			&game->txt.n->width, &game->txt.n->height);
	if (game->txt.n->img)
		game->txt.n->p = mlx_get_data_addr(game->txt.n->img, &game->txt.n->bpp,
				&game->txt.n->size_line, &game->txt.n->endian);
	game->txt.s->img = mlx_xpm_file_to_image(win->mlx,
			game->txt.s->c, &game->txt.s->width, &game->txt.s->height);
	if (game->txt.s->img)
		game->txt.s->p = mlx_get_data_addr(game->txt.s->img, &game->txt.s->bpp,
				&game->txt.s->size_line, &game->txt.s->endian);
	game->txt.e->img = mlx_xpm_file_to_image(win->mlx,
			game->txt.e->c, &game->txt.e->width, &game->txt.e->height);
	if (game->txt.e->img)
		game->txt.e->p = mlx_get_data_addr(game->txt.e->img, &game->txt.e->bpp,
				&game->txt.e->size_line, &game->txt.e->endian);
	game->txt.w->img = mlx_xpm_file_to_image(win->mlx,
			game->txt.w->c, &game->txt.w->width, &game->txt.w->height);
	if (game->txt.w->img)
		game->txt.w->p = mlx_get_data_addr(game->txt.w->img, &game->txt.w->bpp,
				&game->txt.w->size_line, &game->txt.w->endian);
	if (!game->txt.n->img || !game->txt.s->img
		|| !game->txt.e->img || !game->txt.w->img)
		return (print_error("Error\nFailed to load textures\n"),
			close_window(env), (void)env);
}

void	ft_free_textures(t_game *game, t_window *win)
{
	if (game->txt.n->img)
		mlx_destroy_image(win->mlx, game->txt.n->img);
	if (game->txt.s->img)
		mlx_destroy_image(win->mlx, game->txt.s->img);
	if (game->txt.e->img)
		mlx_destroy_image(win->mlx, game->txt.e->img);
	if (game->txt.w->img)
		mlx_destroy_image(win->mlx, game->txt.w->img);
}

void	ft_setplan(t_player *plr, double planeLength)
{
	plr->plane.x = -plr->dir.y * planeLength;
	plr->plane.y = plr->dir.x * planeLength;
}

int	ft_window(t_game *game)
{
	t_env	env;

	env.win.mlx = mlx_init();
	if (!env.win.mlx)
		return (1);
	env.game = *game;
	ft_initp(&env.game, &env.game.plr);
	env.mouse = 0;
	env.win.win = mlx_new_window(env.win.mlx,
			SCREENX, SCREENY, "Cub3d Raytracing");
	if (!env.win.win)
		return (free(env.win.mlx), 1);
	load_textures(&env, &env.game, &env.win);
	ft_draw(&env.game, &env.win);
	mlx_hook(env.win.win, 17, 0, (int (*)())close_window, &env);
	mlx_hook(env.win.win, 2, 1L << 0, key_hook, &env);
	mlx_hook(env.win.win, MotionNotify, 1L << 6, mouse_motion_hook, &env);
	mlx_loop_hook(env.win.mlx, update, &env);
	mlx_loop(env.win.mlx);
	return (0);
}
