/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:53:57 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/18 19:57:48 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checkmap.h>

void	fail_count(t_game *game)
{
	free_ressource(game);
	print_error("\033[0;31mError\033[0m: Bad graphics setting detected!\n");
	exit(0);
}

void	check_is_fail(t_game *game, char *str)
{
	if (!str)
	{
		free(game->line_save);
		free_ressource(game);
		ft_putstr_fd("\033[0;31mError\033[0m: Fail malloc\n", 2);
		exit(0);
	}
}
