/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:17:01 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/03 17:17:01 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checkmap.h>

void	set_color(t_game *game, char *set)
{
	unsigned int	color;

	color = (game->texture.r << 16) | (game->texture.g << 8) | game->texture.b;
	if (!ft_strcmp(set, "F"))
	{
		game->texture.roof_color = color;
		game->texture.count++;
	}
	if (!ft_strcmp(set, "C"))
	{
		game->texture.ground_color = color;
		game->texture.count++;
	}
}

int	skip_spaces(char *line, int i)
{
	if ((line[i] != ' ' || line[i] != '\t'))
		return (i);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int	skip_sep(char *line, int i)
{
	while (line[i] && line[i] != ',')
		i++;
	return (i + 1);
}

int	rgb_check(t_game *game, char *line, int i)
{
	int	n;

	n = 0;
	if (!ft_digit(line[i]))
		return (-1);
	while (line[i] && line[i] != ',')
	{
		if ((line[i] == ' ' || escape_sequences(line[i])))
			break ;
		if (ft_digit(line[i]))
				n = n * 10 + (line[i] - '0');
		else
		{
			free(game->line_save);
			free_ressource(game);
			printf("\033[0;31mError\033[0m: Sorry, wrong graphics color detected !\n");
			exit(0);
		}
		i++;
	}
	return (n);
}

void	check_rgb(t_game *game)
{
	if (game->texture.r < 0 || game->texture.r > 255)
	{
		free(game->line_save);
		free_ressource(game);
		printf("\033[0;31mError\033[0m: Sorry, bad input RGB detected !\n");
		exit(0);
	}
	if (game->texture.g < 0 || game->texture.g > 255)
	{
		free(game->line_save);
		free_ressource(game);
		printf("\033[0;31mError\033[0m: Sorry, bad input RGB detected !\n");
		exit(0);
	}
	if (game->texture.b < 0 || game->texture.b > 255)
	{
		free(game->line_save);
		free_ressource(game);
		printf("\033[0;31mError\033[0m: Sorry, bad input RGB detected !\n");
		exit(0);
	}
}
