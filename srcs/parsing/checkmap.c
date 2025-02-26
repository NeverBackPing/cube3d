/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:23:07 by gtraiman          #+#    #+#             */
/*   Updated: 2025/02/26 19:04:37 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checkmap.h"

int	checkmap(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[0][i])
		if (tab[0][i] != '1' && tab[0][i] != ' ' && tab[0][i] != '\t')
			return (1);
		else
			i++;
	while (tab[++i])
	{
		if (tab[i][0] != '1')
			return (1);
		j = 0;
		while (tab[i][++j])
			if (tab[i][j] != '1' && (ft_strlen(tab[i - 1]) <= (size_t)j || ft_strlen(tab[i + 1]) <= (size_t)j))
				return (1);
		if (tab[i][j] && tab[i][j] != '1')
			return (1);
	}
	j = -1;
	while (tab[i - 1][++j])
		if (tab[i - 1][j] != '1' && tab[i - 1][j] != ' ' && tab[i - 1][j] != '\t')
			return (1);
	return (0);
}

/*int main(int ac, char **av)
{
    if(ac < 2)
        return(printf("Error"));
    char *tab[] =
    {
        "1111 1",
        "100101",
        "101001",
        "1100N1",
        "111111",
        NULL
    };
    printf("%d",checkmap(tab));
}*/