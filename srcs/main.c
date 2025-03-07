/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:48:14 by gtraiman          #+#    #+#             */
/*   Updated: 2025/02/27 18:48:14 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
void ft_printab(char **tab)
{
    int i = 0;
    int j;

    while(tab[i])
    {
        j = 0;
        while(tab[i][j])
        {
            write(1, &tab[i][j], 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}


int	main(int ac, char **av)
{
	t_game	game;

	init_struct(&game);
	if (ac != 2)
		handler_argument(ac);
	handler_fd(av[1]);
	get_set_graph(&game, av[1]);
	get_lenght_map(&game);
	map_init(&game);
	get_map(&game, av[1]);
	map_is_good(&game);
	edit_map(&game);
	// ft_printab(game.map.map);
	ft_window(&game);
	free_ressource(&game);
	return (0);
}
