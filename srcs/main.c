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

#include <../includes/main.h>

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		handler_argument(ac);
	handler_fd(av[1]);
	/*
		1.	open the fd a first time to retrieve the size of the map, close the fd after.
			and store it in length which is in the amap structure

		2.	open the fd again to recover the graphic characters
			if an error is found close the fd and exit with a message

		!! the fd must be stored in the main structure game !!
	*/
	// get_set_graph(&game, av[1]);
	get_map(&game, av[1]);
	return (0);
}
