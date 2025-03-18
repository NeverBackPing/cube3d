/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:50:37 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/18 16:50:37 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/main.h>

void	init_null_str(t_game *game)
{
	game->txt.e->c = NULL;
	game->txt.n->c = NULL;
	game->txt.s->c = NULL;
	game->txt.w->c = NULL;
}

void	init_count(t_game *game)
{
	game->txt.count = 0;
	game->txt.count_c = 0;
	game->txt.count_e = 0;
	game->txt.count_f = 0;
	game->txt.count_n = 0;
	game->txt.count_player = 0;
	game->txt.count_s = 0;
	game->txt.count_w = 0;
}

void	init_struct(t_game *game)
{
	game->fd = -1;
	game->map.lenght = 0;
	game->map.row = 0;
	game->txt.line_save = NULL;
	game->map.map = NULL;
	game->map.lenght_index = 0;
	game->txt.r = -1;
	game->txt.g = -1;
	game->txt.b = -1;
	init_count(game);
	game->txt.roof_color = -1;
	game->txt.ground_color = -1;
	game->txt.e = malloc(sizeof(t_wall));
	game->txt.n = malloc(sizeof(t_wall));
	game->txt.s = malloc(sizeof(t_wall));
	game->txt.w = malloc(sizeof(t_wall));
	if (!game->txt.e || !game->txt.n || !game->txt.s || !game->txt.w)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		exit(1);
	}
	init_null_str(game);
}
