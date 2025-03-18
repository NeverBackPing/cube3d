/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:17:06 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/18 15:23:58 by sjossain         ###   ########.fr       */
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
		if (line[j] != ' ' && line[j] != '\t')
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
	ft_strlcpy(file_xpm, (line + start), max);
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

void	edit_path_set(t_game *game, char **set_graph, char *file_xpm)
{
	char	*tmp;

	tmp = ft_strdup(file_xpm);
	if (!tmp)
	{
		free(file_xpm);
		free_ressource(game);
		ft_putstr_fd("\033[0;31mError\033[0m: Fail malloc\n", 2);
		exit(0);
	}
	*set_graph = ft_strjoin("./", tmp);
	check_is_fail(game, *set_graph);
	game->txt.count++;
	free(tmp);
}

void	alloc_graph_set(t_game *game, char *file_xpm, char *set_graph)
{
	if (game->txt.count == 4)
	{
		free(game->line_save);
		free_ressource(game);
		free(file_xpm);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry, too many graphics setting detected !\n", 2);
		exit(0);
	}
	if (!ft_strcmp(set_graph,"NO"))
		edit_path_set(game, &game->txt.n->c, file_xpm);
	if (!ft_strcmp(set_graph,"SO"))
		edit_path_set(game, &game->txt.s->c, file_xpm);

	if (!ft_strcmp(set_graph,"WE"))
		edit_path_set(game, &game->txt.w->c, file_xpm);
	if (ft_strcmp(set_graph,"EA"))
		return ;
	edit_path_set(game, &game->txt.e->c, file_xpm);
}
