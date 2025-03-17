/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:55:13 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/17 16:06:58 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checkmap.h"

void	get_big_row(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (map->map[i])
	{
		if (!map->map[i][j])
		{
			i++;
			if (count > map->row)
				map->row = count;
			j = 0;
			count = 0;
		}
		j++;
		count++;
	}
}

void	edit_with_space(t_game *game, char *str, t_map *map, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if ((int)ft_strlen(map->map[i]) < game->map.row)
	{
		free(map->map[i]);
		map->map[i] = malloc((game->map.row + 1) * sizeof(char *));
		if (!map->map[i])
		{
			free_ressource(game);
			ft_putstr_fd("\033[0;31mError\033[0m: Fail malloc\n", 2);
			exit(0);
		}
		while (str[k])
		{
			map->map[i][j] = str[k];
			k++;
			j++;
		}
		while (j < game->map.row)
			map->map[i][j++] = ' ';
		map->map[i][j] = '\0';
	}
}

void	add_space(t_game *game)
{
	int		i;
	char	*str;

	i = 0;
	while (game->map.map[i])
	{
		str = ft_strdup(game->map.map[i]);
		if (!str)
		{
			free_ressource(game);
			ft_putstr_fd("\033[0;31mError\033[0m: Fail malloc\n", 2);
			exit(0);
		}
		edit_with_space(game, str, &game->map, i);
		if (str)
		{
			free(str);
			str = NULL;
		}
		i++;
	}
}

void	edit_map(t_game *game)
{
	get_big_row(&game->map);
	add_space(game);
	if (game->map.lenght > 50 && game->map.row > 130)
		ft_putstr_fd("\033[0;31mError\033[0m: Sory cant draw minimap\n", 2);
}
