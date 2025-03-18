/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:56:37 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/18 16:19:43 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"

t_vec	ft_move(t_vec *pos, t_vec *dir, t_game *game, int keycode)
{
	t_vec	newpos;

	newpos.x = 0;
	if (keycode == 119)
	{
		newpos.x = pos->x + (0.001 + dir->x) * SPEED;
		newpos.y = pos->y + (0.001 + dir->y) * SPEED;
	}
	else if (keycode == 115)
	{
		newpos.x = pos->x - (0.001 + dir->x) * SPEED;
		newpos.y = pos->y - (0.001 + dir->y) * SPEED;
	}
	else if (keycode == 97)
	{
		newpos.x = pos->x + (0.001 + dir->y) * SPEED;
		newpos.y = pos->y - (0.001 + dir->x) * SPEED;
	}
	else if (keycode == 100)
	{
		newpos.x = pos->x - (0.001 + dir->y) * SPEED;
		newpos.y = pos->y + (0.001 + dir->x) * SPEED;
	}
	(void)keycode;
	return (ft_testpos(newpos, pos, game));
}

t_vec	ft_testpos(t_vec newpos, t_vec *pos, t_game *game)
{
	t_vec	pos_try;

	if (game->map.map[(int)newpos.y][(int)newpos.x] != '1')
		if (game->map.map[(int)newpos.y][(int)pos->x] != '1')
			if (game->map.map[(int)pos->y][(int)pos->x] != '1')
				return (newpos);
	pos_try.x = newpos.x;
	pos_try.y = pos->y;
	if (game->map.map[(int)pos_try.y][(int)pos_try.x] != '1')
		return (pos_try);
	pos_try.x = pos->x;
	pos_try.y = newpos.y;
	if (game->map.map[(int)pos_try.y][(int)pos_try.x] != '1')
		return (pos_try);
	return (*pos);
}

void	ft_findp(char **map, t_vec *pos)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_cins("NESW", map[i][j]) == 1)
			{
				pos->y = i + 0.5;
				pos->x = j + 0.5;
				if (map[i][j] == 'E')
					pos->x--;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_initp(t_game *game, t_player *plr)
{
	ft_findp(game->map.map, &plr->pos);
	plr->dir.y = 0;
	plr->dir.x = 0;
	if (game->map.map[(int)plr->pos.y][(int)plr->pos.x] == 'N')
		plr->dir.y = 1;
	else if (game->map.map[(int)plr->pos.y][(int)plr->pos.x] == 'S')
		plr->dir.y = -1;
	else if (game->map.map[(int)plr->pos.y][(int)plr->pos.x] == 'W')
		plr->dir.x = -1;
	else
		plr->dir.x = 1;
	ft_setplan(plr, FOV);
}
