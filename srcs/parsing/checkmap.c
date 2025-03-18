/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:23:07 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/18 17:03:06 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checkmap.h"
#include "../window/window.h"

int	ft_cins(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	ft_whilemap(char **tab, int i, int j, int *cpt)
{
	while (tab[i + 1])
	{
		if (tab[i][0] == '0')
			return (-1);
		j = 1;
		while (tab[i][j])
		{
			if (ft_cins("0NEWS", tab[i][j]) == 1)
			{
				if (tab[i][j] != '0')
					(*cpt)++;
				if (ft_strlen(tab[i - 1]) < j || ft_strlen(tab[i + 1]) < j)
					return (-1);
				if (ft_cins("0NEWS1", tab[i - 1][j]) == 0
					|| ft_cins("0NEWS1", tab[i + 1][j]) == 0)
					return (-1);
				if ((j != 0 && ft_cins("0NEWS1", tab[i][j - 1]) == 0)
					|| ft_cins("0NEWS1", tab[i][j + 1]) == 0)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (i);
}

int	checkmap(char **tab)
{
	int	i;
	int	j;
	int	cpt;

	i = 0;
	j = 0;
	cpt = 0;
	while (tab[i][j])
	{
		if (ft_cins(NEXTO1, tab[i][j]) != 1)
			return (1);
		j++;
	}
	i = ft_whilemap(tab, i + 1, j, &cpt);
	if (i == -1 || cpt != 1)
		return (1);
	j = 0;
	while (tab[i][j])
	{
		if (ft_cins(NEXTO1, tab[i][j]) != 1)
			return (1);
		j++;
	}
	return (0);
}

void	map_is_good(t_game *game)
{
	if (checkmap(game->map.map))
	{
		ft_putstr_fd("\033[0;31mError\033[0m: Bad config in map detected!\n", 2);
		free_ressource(game);
		exit(0);
	}
}
