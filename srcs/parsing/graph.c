/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:17:12 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/03 17:17:12 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checkmap.h"

void	store_path_fd(t_game *game, char *line, char *set_graph)
{
	int			start;
	int			end;
	int			i;
	int			max;
	char		*file_xpm;

	i = 0;
	start = 0;
	end = 0;
	if (!ft_strstr(line, ".xpm"))
	{
		free(game->line_save);
		free_ressource(game);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry, no file.xpm found !\n", 2);
		exit(0);
	}
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && !escape_sequences(line[i]))
		i++;
	end = i + 1;
	check_xpm(game, line, start, end);
	max = end - start;
	file_xpm = malloc((max + 2) * sizeof(char));
	ft_strlcpy(file_xpm, (line + start), end);
	alloc_graph_set(game, file_xpm, set_graph);
	free(file_xpm);
}

void	check_sep(t_game *game, char *line)
{
	int	i;
	int	count_sep;

	i = 0;
	count_sep = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count_sep++;
		i++;
	}
	if (count_sep != 2)
	{
		free(game->line_save);
		free_ressource(game);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry, bad input RGB detected !\n", 2);

		exit(0);
	}
}

void	store_rgb(t_game *game, char *line, char *set_graph)
{
	int	i;

	i = 0;
	if (game->texture.count == 6)
	{
		free(game->line_save);
		free_ressource(game);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry, too many graphics setting detected !\n", 2);
		exit(0);
	}
	check_sep(game, line);
	i = skip_spaces(line, i);
	game->texture.r = rgb_check(game, line, i);
	i = skip_sep(line, i);
	game->texture.g = rgb_check(game, line, i);
	i = skip_sep(line, i);
	game->texture.b = rgb_check(game, line, i);
	check_rgb(game);
	set_color(game, set_graph);

}

void	check_set_graph(t_game *game, char *line, char *set_graph)
{
	int	i;

	i = find_index(line, set_graph);
	if (i - 1 != find_first_word_end_index(line))
	{
		free(game->line_save);
		free_ressource(game);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry, wrong graphics setting detected !\n", 2);
		exit(0);
	}
	if (ft_strstr(line, "NO"))
		store_path_fd(game, (line + i), "NO");
	if (ft_strstr(line, "SO"))
		store_path_fd(game, (line + i), "SO");
	if (ft_strstr(line, "WE"))
		store_path_fd(game, (line + i), "WE");
	if (ft_strstr(line, "EA"))
		store_path_fd(game, (line + i), "EA");
	if (ft_strstr(line, "F"))
		store_rgb(game, (line + i), set_graph);
	if (ft_strstr(line, "C"))
		store_rgb(game, (line + i), set_graph);
}

void	set_graphique(t_game *game, char *line)
{
	int			i;
	int			count_word;
	const char	*set_graph[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};

	i = 0;
	game->line_save = line;
	while (set_graph[i])
	{
		count_word = 0;
		if (ft_strstr(line, set_graph[i]))
		{
			count_word = words(line);
			if (count_word <= 3 && count_word >= 2)
				check_set_graph(game, line, (char *)set_graph[i]);
			else
			{
				free(game->line_save);
				free_ressource(game);
				ft_putstr_fd("\033[0;31mError\033[0m: Sorry, wrong graphics setting detected !\n", 2);
				exit(0);
			}
		}
		i++;
	}
}

void	get_set_graph(t_game *game, char *filename)
{
	char	*line;

	open_fd(game, filename);
	while (1 && game->texture.count != 6)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		if (!escape_sequences(line[0]))
		{
			if (!just_space(line))
				set_graphique(game, line);
		}
		if (line)
			free(line);
		line = NULL;
	}
	if (game->texture.count !=  GRAPH_CHECK)
	{
		free_ressource(game);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry, wrong graphics setting detected!\n", 2);
		exit(0);
	}
}
