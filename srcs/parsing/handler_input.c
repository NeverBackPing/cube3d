/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:17:17 by sjossain          #+#    #+#             */
/*   Updated: 2025/03/03 17:17:17 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checkmap.h"

void	handler_argument(int ac)
{
	if (ac < 2)
		print_error("\033[0;31mError\033[0m: <./cube3d filename.cub>\n");
	else
		ft_putstr_fd("\033[0;31mError\033[0m: Sorry to many argument !\n", 2);
	exit(0);
}
