/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:51:29 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/18 17:51:11 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"

void	calculate_wallx(t_ray *r, t_player *plr)
{
	if (r->side == 0)
		r->wallx = plr->pos.y + r->perpwalldist * r->raydir.y;
	else
		r->wallx = plr->pos.x + r->perpwalldist * r->raydir.x;
	r->wallx -= floor(r->wallx);
}

void	calculate_texx(t_ray *r, int texWidth)
{
	r->texx = (int)(r->wallx * (double)texWidth);
	if (r->side == 0 && r->raydir.x > 0)
		r->texx = texWidth - r->texx - 1;
	if (r->side == 1 && r->raydir.y < 0)
		r->texx = texWidth - r->texx - 1;
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_setposmap(t_ray *r)
{
	r->mapx = (int)r->raydir.x;
	r->mapy = (int)r->raydir.y;
}

void	ft_setdelta(t_ray *r)
{
	if (r->raydir.x == 0)
		r->deltadist.x = 1e30;
	else
		r->deltadist.x = fabs(1 / r->raydir.x);
	if (r->raydir.y == 0)
		r->deltadist.y = 1e30;
	else
		r->deltadist.y = fabs(1 / r->raydir.y);
}
