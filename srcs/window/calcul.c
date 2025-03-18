/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:18 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/18 17:51:11 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"

void	ft_setsidedist(t_ray *r, double posX, double posY)
{
	if (r->raydir.x < 0)
	{
		r->stepx = -1;
		r->sidedist.x = (posX - r->mapx) * r->deltadist.x;
	}
	else
	{
		r->stepx = 1;
		r->sidedist.x = (r->mapx + 1.0 - posX) * r->deltadist.x;
	}
	if (r->raydir.y < 0)
	{
		r->stepy = -1;
		r->sidedist.y = (posY - r->mapy) * r->deltadist.y;
	}
	else
	{
		r->stepy = 1;
		r->sidedist.y = (r->mapy + 1.0 - posY) * r->deltadist.y;
	}
}

void	ft_testhit(t_ray *r, t_game *game, int hit)
{
	while (hit == 0)
	{
		if (r->sidedist.x < r->sidedist.y)
		{
			r->sidedist.x += r->deltadist.x;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedist.y += r->deltadist.y;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (r->mapy < 0 || r->mapy >= ft_tablen(game->map.map)
			|| r->mapx < 0 || r->mapx >= ft_strlen(game->map.map[r->mapy]))
				hit = 1;
		if (game->map.map[r->mapy][r->mapx] == '1')
			hit = 1;
	}
	if (r->side == 0)
		r->perpwalldist = r->sidedist.x - r->deltadist.x;
	else
		r->perpwalldist = r->sidedist.y - r->deltadist.y;
}

t_vec	ft_onecol(int x, t_player plr)
{
	double	camx;
	t_vec	raydir;

	camx = 2 * x / (double)SCREENX - 1;
	raydir.x = plr.dir.x + plr.plane.x * camx;
	raydir.y = plr.dir.y + plr.plane.y * camx;
	return (raydir);
}

void	ft_init_ray(t_ray *r, t_game *game, int x)
{
	r->raydir = ft_onecol(x, game->plr);
	r->mapx = (int)game->plr.pos.x;
	r->mapy = (int)game->plr.pos.y;
	ft_setdelta(r);
	ft_setsidedist(r, game->plr.pos.x, game->plr.pos.y);
	ft_testhit(r, game, 0);
	r->lh = (int)(SCREENY / r->perpwalldist);
	r->ds = -r->lh / 2 + SCREENY / 2;
	if (r->ds < 0)
		r->ds = 0;
	r->de = r->lh / 2 + SCREENY / 2;
	if (r->de >= SCREENY)
		r->de = SCREENY - 1;
	r->texture = ft_get_texture(game, r);
}

void	ft_allcol(t_game *game, char *data, t_window *win)
{
	int			x;
	t_ray		r;

	x = 0;
	while (x < SCREENX)
	{
		ft_init_ray(&r, game, x);
		calculate_wallx(&r, &game->plr);
		calculate_texx(&r, r.texture->width);
		draw_textured_wall(&r, x, data, win);
		x++;
	}
}
