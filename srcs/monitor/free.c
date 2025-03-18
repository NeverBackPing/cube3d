/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:30:44 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/18 19:31:07 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/main.h>

void	init_null(t_game *game)
{
	game->txt.e = NULL;
	game->txt.n = NULL;
	game->txt.s = NULL;
	game->txt.w = NULL;
}

void	free_ressource_prt2(t_game *game)
{
	if (game->txt.s)
	{
		if (game->txt.s->c)
			free(game->txt.s->c);
		free(game->txt.s);
	}
	if (game->txt.w)
	{
		if (game->txt.w->c)
			free(game->txt.w->c);
		free(game->txt.w);
	}
}

void	free_ressource(t_game *game)
{
	close_fd(game);
	if (game->txt.e)
	{
		if (game->txt.e->c)
			free(game->txt.e->c);
		free(game->txt.e);
	}
	if (game->txt.n)
	{
		if (game->txt.n->c)
			free(game->txt.n->c);
		free(game->txt.n);
	}
	free_ressource_prt2(game);
	if (game->map.map)
		dest_free(game->map.map);
	init_null(game);
}
