#include "checkmap.h"

bool	escape_sequences(char c)
{
	if (c == '\n' || c == '\r' || c == '\t')
		return (true);
	return (false);
}

void	alloc_map(t_game *game, t_map *map, int lengh, char *line)
{
	if (map->lenght_index < map->lenght)
	{
		map->map[map->lenght_index] = malloc((lengh + 1) * sizeof(char *));
		if (!map->map[map->lenght_index])
		{
			close_fd(game);
			dest_free(map->map);
			free(game->texture.north_texture);
			free(game->texture.east_texture);
			free(game->texture.south_texture);
			free(game->texture.west_texture);
			printf("\033[0;31mError\033[0m: Fail malloc \n");
			exit(0);
		}
		ft_strlcpy(map->map[map->lenght_index], line, lengh);
		map->lenght_index++;
	}
	else
		map->map[map->lenght] = NULL;
}

void	start_cpy_map(t_game *game, t_map *map, char *line)
{
	int	i;
	int	lengh;

	i = 0;
	lengh = 0;
	(void) game;
	while (line[i])
	{
		if (line[i] == ' ')
			line[i] = 1;
		i++;
		if (!escape_sequences(line[i]))
			lengh++;
	}
	alloc_map(game, map, lengh, line);
}


bool	just_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && !escape_sequences(line[i]))
			return (false);
		i++;
	}
	return (true);
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
			if (!just_space(line))
				start_cpy_map(game, &game->map, line);
		}
	}
	close_fd(game);
	game->map.map = NULL;
}
