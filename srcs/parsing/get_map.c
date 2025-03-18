/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:16:55 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/03 17:16:55 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checkmap.h"

void	alloc_map(t_game *game, t_map *map, int lengh, char *line)
{
	if (map->lenght_index < map->lenght)
	{
		map->map[map->lenght_index] = malloc((lengh + 1) * sizeof(char *));
		if (!map->map[map->lenght_index])
		{
			close_fd(game);
			dest_free(map->map);
			free(game->txt.n->c);
			free(game->txt.e->c);
			free(game->txt.s->c);
			free(game->txt.w->c);
			ft_putstr_fd("\033[0;31mError\033[0m: Fail malloc \n", 2);
			exit(0);
		}
		ft_strlcpy(map->map[map->lenght_index], line, lengh);
		map->lenght_index++;
	}
}

void	start_cpy_map(t_game *game, t_map *map, char *line)
{
	int	i;
	int	lengh;

	i = 0;
	lengh = 0;
	while (line[i])
	{
		if (!escape_sequences(line[i]))
			lengh++;
		i++;
	}
	alloc_map(game, map, lengh, line);
}

bool	just_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && \
			!escape_sequences(line[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	skip_set_graph(char *line)
{
	int			i;
	const char	*set_graph[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};

	i = 0;
	while (set_graph[i])
	{
		if (ft_strstr(line, set_graph[i]))
			return (true);
		i++;
	}
	return (false);
}

void	get_map(t_game *game, char *filename)
{
	char	*line;

	open_fd(game, filename);
	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		if (!escape_sequences(line[0]))
		{
			if (!just_space(line) && !skip_set_graph(line))
			{
				start_cpy_map(game, &game->map, line);
			}
		}
		if (line)
			free(line);
	}
	close_fd(game);
	game->map.map[game->map.lenght] = NULL;
}
