/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:30:00 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/07 00:00:52 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	ft_draw_background(t_game *game, char *data, int size_line)
{
	int	x;
	int	y;
	int	*img_data;

	y = 0;
	img_data = (int *)data;
	while (y < SCREENY)
	{
		x = 0;
		while (x < SCREENX)
		{
			if (y < SCREENY / 2)
				img_data[y * (size_line / 4) + x] = game->txt.ground_color;
			else
				img_data[y * (size_line / 4) + x] = game->txt.roof_color;
			x++;
		}
		y++;
	}
}
