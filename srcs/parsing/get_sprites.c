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
		printf("\033[0;31mError\033[0m: Sorry I can't open $%s$\n", file_xpm);
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
		printf("\033[0;31mError\033[0m: Fail malloc\n");
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
		printf("\033[0;31mError\033[0m: Sorry, too many graphics setting detected !\n");
		exit(0);
	}
	if (!ft_strcmp(set_graph,"NO"))
	{
		game->texture.north_texture = ft_strdup(file_xpm);
		check_is_fail(game, game->texture.north_texture);
		game->texture.count++;
	}
	if (!ft_strcmp(set_graph,"SO"))
	{
		game->texture.south_texture = ft_strdup(file_xpm);
		check_is_fail(game, game->texture.south_texture);
		game->texture.count++;

	}
	if (!ft_strcmp(set_graph,"WE"))
	{
		game->texture.west_texture = ft_strdup(file_xpm);
		check_is_fail(game, game->texture.west_texture);
		game->texture.count++;

	}
	if (ft_strcmp(set_graph,"EA"))
		return ;
	game->texture.east_texture = ft_strdup(file_xpm);
	check_is_fail(game, game->texture.east_texture);
	game->texture.count++;
}
