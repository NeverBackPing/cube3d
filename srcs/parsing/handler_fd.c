/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:17:14 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/03 17:17:14 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checkmap.h"

void	close_fd(t_game *game)
{
	if (game->fd > 0)
	{
		close(game->fd);
		game->fd = -1;
	}
}

void	open_fd(t_game *game, char *filename)
{
	if (game->fd > 0)
		return ;
	game->fd = -1;
	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
	{
		free_ressource(game);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry I can't open the fd\n", 2);
		exit(0);
	}
}

void	handler_fd(char	*fd)
{
	int	i;
	int	egal;

	i = 0;
	egal = 0;
	while (fd[i] && fd[i] != '.')
		i++;
	egal = ft_strcmp((fd + i), ".cub");
	if (egal != 0)
	{
		ft_putstr_fd("\033[0;31mError\033[0m: Bad file extension\n", 2);
		exit(0);
	}
}
