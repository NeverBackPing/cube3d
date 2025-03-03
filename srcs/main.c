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

int	main(int ac, char **av)
{
	t_game	game;

	init_struct(&game);
	if (ac != 2)
		handler_argument(ac);
	handler_fd(av[1]);
	get_set_graph(&game, av[1]);
	get_lenght_map(&game);
	//get_map(&game);
	//ft_window();
	free_ressource(&game);
	return (0);
}
