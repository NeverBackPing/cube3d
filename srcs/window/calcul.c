/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:18 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/18 15:58:26 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"

void	ft_setsidedist(t_ray *r, double posX, double posY)
{
	if (r->rayDir.x < 0)
	{
		r->stepX = -1;
		r->sideDist.x = (posX - r->mapX) * r->deltaDist.x;
	}
	else
	{
		r->stepX = 1;
		r->sideDist.x = (r->mapX + 1.0 - posX) * r->deltaDist.x;
	}
	if (r->rayDir.y < 0)
	{
		r->stepY = -1;
		r->sideDist.y = (posY - r->mapY) * r->deltaDist.y;
	}
	else
	{
		r->stepY = 1;
		r->sideDist.y = (r->mapY + 1.0 - posY) * r->deltaDist.y;
	}
}

void	ft_testhit(t_ray *r, t_game *game, int hit)
{
	while (hit == 0)
	{
		if (r->sideDist.x < r->sideDist.y)
		{
			r->sideDist.x += r->deltaDist.x;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDist.y += r->deltaDist.y;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (r->mapY < 0 || r->mapY >= ft_tablen(game->map.map)
			|| r->mapX < 0 || r->mapX >= (int)ft_strlen(game->map.map[r->mapY]))
				hit = 1;
		if (game->map.map[r->mapY][r->mapX] == '1')
			hit = 1;
	}
	if (r->side == 0)
		r->perpWallDist = r->sideDist.x - r->deltaDist.x;
	else
		r->perpWallDist = r->sideDist.y - r->deltaDist.y;
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
	r->rayDir = ft_onecol(x, game->plr);
	r->mapX = (int)game->plr.pos.x;
	r->mapY = (int)game->plr.pos.y;
	ft_setdelta(r);
	ft_setsidedist(r, game->plr.pos.x, game->plr.pos.y);
	ft_testhit(r, game, 0);
	r->lh = (int)(SCREENY / r->perpWallDist);
	r->Ds = -r->lh / 2 + SCREENY / 2;
	if (r->Ds < 0)
		r->Ds = 0;
	r->De = r->lh / 2 + SCREENY / 2;
	if (r->De >= SCREENY)
		r->De = SCREENY - 1;
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
