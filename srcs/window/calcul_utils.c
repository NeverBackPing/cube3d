/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:51:29 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/18 15:59:07 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"

void	calculate_wallx(t_ray *r, t_player *plr)
{
	if (r->side == 0)
		r->wallX = plr->pos.y + r->perpWallDist * r->rayDir.y;
	else
		r->wallX = plr->pos.x + r->perpWallDist * r->rayDir.x;
	r->wallX -= floor(r->wallX);
}

void	calculate_texx(t_ray *r, int texWidth)
{
	r->texX = (int)(r->wallX * (double)texWidth);
	if (r->side == 0 && r->rayDir.x > 0)
		r->texX = texWidth - r->texX - 1;
	if (r->side == 1 && r->rayDir.y < 0)
		r->texX = texWidth - r->texX - 1;
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
	r->mapX = (int)r->rayDir.x;
	r->mapY = (int)r->rayDir.y;
}

void	ft_setdelta(t_ray *r)
{
	if (r->rayDir.x == 0)
		r->deltaDist.x = 1e30;
	else
		r->deltaDist.x = fabs(1 / r->rayDir.x);
	if (r->rayDir.y == 0)
		r->deltaDist.y = 1e30;
	else
		r->deltaDist.y = fabs(1 / r->rayDir.y);
}
