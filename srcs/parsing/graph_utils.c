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

void	free_ressource(t_game *game)
{
	close_fd(game);
	if (game->texture.east_texture)
		free(game->texture.east_texture);
	if (game->texture.north_texture)
		free(game->texture.north_texture);
	if (game->texture.south_texture)
		free(game->texture.south_texture);
	if (game->texture.west_texture)
		free(game->texture.west_texture);
	game->texture.east_texture = NULL;
	game->texture.north_texture = NULL;
	game->texture.south_texture = NULL;
	game->texture.west_texture = NULL;
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
