/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:45:20 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/18 15:59:17 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"

int	key_hook(int keycode, void	*param)
{
	t_env	*env;

	env = (t_env *)param;
	if (keycode == 65307)
		close_window(env);
	if (keycode == 65361)
		env->game.plr.dir = turnv(env->game.plr.dir, -RADTURN);
	else if (keycode == 65363)
		env->game.plr.dir = turnv(env->game.plr.dir, RADTURN);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		env->game.plr.pos = ft_move(&env->game.plr.pos,
				&env->game.plr.dir, &env->game, keycode);
	ft_setplan(&env->game.plr, FOV);
	ft_draw(&env->game, &env->win);
	return (0);
}

int	update(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->game.plr.dir = turnv(env->game.plr.dir,
			RADTURN *(-((double)env->mouse) / 10.0));
	ft_setplan(&env->game.plr, FOV);
	ft_draw(&env->game, &env->win);
	return (0);
}

int	mouse_motion_hook(int x, int y, void *param)
{
	t_env	*env;

	(void)y;
	env = (t_env *)param;
	if (x < SCREENX / 5 * 0.5)
		env->mouse = 8;
	else if (x > SCREENX - SCREENX / 5 * 0.5)
		env->mouse = -8;
	else if (x < SCREENX / (5 * 1.3))
		env->mouse = 4;
	else if (x > SCREENX - SCREENX / 5 * 1.3)
		env->mouse = -4;
	else if (x < SCREENX / 2 - SCREENX / 5 * 0.6)
		env->mouse = 2;
	else if (x > SCREENX / 2 + SCREENX / 5 * 0.6)
		env->mouse = -2;
	else if (x < SCREENX / 2 - SCREENX / 5 * 0.3)
		env->mouse = 1;
	else if (x > SCREENX / 2 + SCREENX / 5 * 0.3)
		env->mouse = -1;
	else
		env->mouse = 0;
	return (0);
}

t_vec	turnv(t_vec v, double rad)
{
	t_vec	rotated;

	rotated.x = v.x * cos(rad) - v.y * sin(rad);
	rotated.y = v.x * sin(rad) + v.y * cos(rad);
	return (rotated);
}
