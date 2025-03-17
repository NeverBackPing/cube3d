/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:17:06 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/17 18:12:20 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checkmap.h>

int	find_index(char *line, char *str)
{
	int	i;
	int	j;
	int	save;

	i = 0;
	j = 0;
	while (line[i])
	{
		j = 0;
		while (str[j] && line[i + j] == str[j])
			j++;
		if (!str[j])
			break ;
		i++;
	}
	j = i + j;
	save = j;
	while (line[j])
	{
		if (line[j] != ' ')
			return (save + 1);
		j++;
	}
	return (-1);
}

void	check_xpm(t_game *game, char *line, int start, int end)
{
	int			fd;
	const int	max = end - start;
	char		file_xpm[max];

	fd = -1;
	ft_strlcpy(file_xpm, (line + start), max - 1);
	fd = open(file_xpm, O_RDONLY);
	if (fd < 0)
	{
		free(game->line_save);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry I can't open ", 2);
		ft_putstr_fd(file_xpm, 2);
		ft_putstr_fd("\n", 2);
		free_ressource(game);
		exit(0);
	}
	close (fd);
	fd = -1;
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

void	alloc_graph_set(t_game *game, char *file_xpm, char *set_graph)
{
	if (game->texture.count == 4)
	{
		free(game->line_save);
		free_ressource(game);
		free(file_xpm);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry, too many graphics setting detected !\n", 2);
		exit(0);
	}
	if (!ft_strcmp(set_graph,"NO"))
	{
		game->texture.north->c = ft_strdup(file_xpm);
		check_is_fail(game, game->texture.north->c);
		game->texture.count++;
	}
	if (!ft_strcmp(set_graph,"SO"))
	{
		game->texture.south->c = ft_strdup(file_xpm);
		check_is_fail(game, game->texture.south->c);
		game->texture.count++;

	}
	if (!ft_strcmp(set_graph,"WE"))
	{
		game->texture.west->c = ft_strdup(file_xpm);
		check_is_fail(game, game->texture.west->c);
		game->texture.count++;

	}
	if (ft_strcmp(set_graph,"EA"))
		return ;
	game->texture.east->c = ft_strdup(file_xpm);
	check_is_fail(game, game->texture.east->c);
	game->texture.count++;
}
