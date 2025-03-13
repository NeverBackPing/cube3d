/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:30:00 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/07 00:00:52 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"

void	draw_tile(t_window *win, int *img_data, int color, int size_line)
{
	int			j;
	int			i;
	const int	end_x = win->minimap.start_x + TILE_SIZE;
	const int	end_y = win->minimap.start_y + TILE_SIZE;

	i = win->minimap.start_y;
	while (i < end_y)
	{
		j = win->minimap.start_x;
		while (j < end_x)
		{
			img_data[i * (size_line / 4) + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_orientation(t_game *game, t_window *win, int *img_data, \
		int size_line)
{
	int		i;
	int		j;
	double	angle;

	i = 0;
	angle = atan2(game->plr.dir.y, game->plr.dir.x);
	win->minimap.orientation_x = win->minimap.px + PLAYER_SIZE / 2 + \
		cos(angle) * (PLAYER_SIZE / 2);
	win->minimap.orientation_y = win->minimap.py + PLAYER_SIZE / 2 + \
		sin(angle) * (PLAYER_SIZE / 2);
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			if (win->minimap.orientation_x + i < size_line / 4 && \
				win->minimap.orientation_y + j < size_line / 4)
				img_data[(win->minimap.orientation_y + j) * (size_line / 4) + \
					(win->minimap.orientation_x + i)] = 0x000000;
			j++;
		}
		i++;
	}
}

void	draw_player_minimap(t_game *game, t_window *win, int *img_data, \
		int size_line)
{
	int	i;
	int	j;

	i = 0;
	win->minimap.px = game->plr.pos.x * TILE_SIZE;
	win->minimap.py = game->plr.pos.y * TILE_SIZE;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			if (win->minimap.px + i < size_line / 4 && \
				win->minimap.py + j < size_line / 4)
				img_data[(win->minimap.py + j) * (size_line / 4) + \
					(win->minimap.px + i)] = 0xFF0000;
			j++;
		}
		i++;
	}
	draw_orientation(game, win, img_data, size_line);
}

void	init_start(t_window *win, int x, int y)
{
	win->minimap.start_x = x * TILE_SIZE;
	win->minimap.start_y = y * TILE_SIZE;
}

void	draw_minimap(t_game *game, char *data, t_window *win, int size_line)
{
	int	x;
	int	y;
	int	color;
	int	*img_data;

	y = 0;
	img_data = (int *)data;
	while (y < ft_tablen(game->map.map))
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.map[y]))
		{
			if (game->map.map[y][x] == '1' || game->map.map[y][x] == ' ')
				color = 0x000000;
			else
				color = 0xFFFFFF;
			init_start(win, x, y);
			draw_tile(win, img_data, color, size_line);
			x++;
		}
		y++;
	}
	draw_player_minimap(game, win, img_data, size_line);
}
