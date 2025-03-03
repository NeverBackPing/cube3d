/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:17:21 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/03 18:57:55 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checkmap.h"

void	count_player(t_game *game, char *line)
{

	if (ft_strstr(line, "N") || ft_strstr(line, "S")\
			ft_strstr(line, "E") || ft_strstr(line, "W"))
			game->texture.count_player++;
	{
		if (game->texture.count_player > 1)
		{
			close(game);
			free_ressource(game);
			ft_putstr_fd(\
				"\033[0;31mError\033[0m: Sorry, too many player in map!\n", 2);
			exit(0);
		}
	}
}

void	count_len_map(t_game *game, char *line)
{
	int		i;
	char	*set_map[] = "01NSEW";

	i = 0;
	while (line[i])
	{
		count_player(game, line[i]);
		i++;
	}
}

void	get_lenght_map(t_game *game)
{
	char	*line;
	int		count;

	line = NULL;
	count = 0;
	while (1)
	{
		line = get_next_line(game->fd);
		printf("%s\n", line);
		if (!line)
			break ;
		if (!escape_sequences(line[0]))
		{
			if (just_space(line))
				count_len_map(game, line)
		}
		if (line)
			free(line);
	}
	game->map.lenght = count;
}
