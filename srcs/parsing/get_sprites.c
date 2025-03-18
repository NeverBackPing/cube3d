/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:17:06 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/18 19:59:25 by sjossain         ###   ########.fr       */
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
	char		*file_xpm;
	const int	max = end - start;

	fd = -1;
	file_xpm = malloc((max + 1) * sizeof(char *));
	if (!file_xpm)
		check_fail(game);
	ft_strlcpy(file_xpm, (line + start), max);
	fd = open(file_xpm, O_RDONLY);
	if (fd < 0)
	{
		free(game->line_save);
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry I can't open ", 2);
		ft_putstr_fd(file_xpm, 2);
		ft_putstr_fd("\n", 2);
		free(file_xpm);
		free_ressource(game);
		exit(0);
	}
	free(file_xpm);
	close (fd);
	fd = -1;
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
	free(tmp);
	check_is_fail(game, *set_graph);
}

void	alloc_graph_set_prt2(t_game *game, char *file_xpm, char *set_graph)
{
	if (!ft_strcmp(set_graph, "WE"))
	{
		if (game->txt.count_w != 0)
			return ;
		edit_path_set(game, &game->txt.w->c, file_xpm);
		game->txt.count_w = 1;
	}
	if (ft_strcmp(set_graph, "EA"))
		return ;
	if (game->txt.count_e != 0)
		return ;
	edit_path_set(game, &game->txt.e->c, file_xpm);
	game->txt.count_e = 1;
}

void	alloc_graph_set(t_game *game, char *file_xpm, char *set_graph)
{
	if (game->txt.count == 4)
	{
		free(game->line_save);
		free_ressource(game);
		free(file_xpm);
		print_error("\033[0;31mError\033[0m: too many setting detected\n");
		exit(0);
	}
	if (!ft_strcmp(set_graph, "NO"))
	{
		if (game->txt.count_n != 0)
			return ;
		edit_path_set(game, &game->txt.n->c, file_xpm);
		game->txt.count_n = 1;
	}
	if (!ft_strcmp(set_graph, "SO"))
	{
		if (game->txt.count_s != 0)
			return ;
		edit_path_set(game, &game->txt.s->c, file_xpm);
		game->txt.count_s = 1;
	}
	alloc_graph_set_prt2(game, file_xpm, set_graph);
}
