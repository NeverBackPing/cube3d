/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:17:09 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/03 17:17:09 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checkmap.h>

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
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry, \
			bad input RGB detected !\n", 2);
		exit(0);
	}
}

void	set_fail(t_game *game)
{
	free(game->line_save);
	free_ressource(game);
	ft_putstr_fd("\033[0;31mError\033[0m: bad setting graph\n", 2);
	exit(0);
}

void	check_fail(t_game *game)
{
	ft_putstr_fd("\033[0;31mError\033[0m: Fail malloc\n", 2);
	free(game->line_save);
	free_ressource(game);
	exit(0);
}

bool	escape_sequences(char c)
{
	if (c == '\n' || c == '\r')
		return (true);
	return (false);
}

int	find_first_word_end_index(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
		return (-1);
	while (line[i] && line[i] != ' ' && !escape_sequences(line[i]))
		i++;
	return (i);
}
