/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:53:33 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/18 19:24:13 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"

void	ft_draw(t_game *game, t_window *win)
{
	int		endian;
	char	*data;

	win->img = mlx_new_image(win->mlx, SCREENX, SCREENY);
	if (!win->img)
		return ;
	data = mlx_get_data_addr(win->img, &win->bpp, &win->size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(win->mlx, win->img);
		return ;
	}
	ft_draw_background(game, data, win->size_line);
	ft_allcol(game, data, win);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	draw_minimap(game, data, win, win->size_line);
	mlx_destroy_image(win->mlx, win->img);
}

int	get_texture_color(t_ray *r, int texx, int texy)
{
	int	offset;

	if (!r->texture)
	{
		print_error("Error\nTexture is NULL\n");
		return (0);
	}
	if (!r->texture->p)
	{
		print_error("Error\nTexture data is NULL\n");
		return (0);
	}
	if (texx < 0 || texx >= r->texture->width || texy < 0
		|| texy >= r->texture->height)
	{
		print_error("Error\nTexture coordinates out of bounds\n");
		return (0);
	}
	offset = texy * r->texture->size_line + texx * (r->texture->bpp / 8);
	if (offset < 0 || offset >= r->texture->size_line * r->texture->height)
	{
		print_error("Error\nInvalid offset\n");
		return (0);
	}
	return (*(int *)(r->texture->p + offset));
}

void	draw_textured_wall(t_ray *r, int x, char *data, t_window *win)
{
	int				y;
	double			step;
	unsigned int	color;
	int				offset;

	step = 1.0 * r->texture->height / r->lh;
	r->texpos = (r->ds - SCREENY / 2 + r->lh / 2) * step;
	y = r->ds;
	while (y < r->de)
	{
		r->texy = (int)r->texpos & (r->texture->height - 1);
		r->texpos += step;
		color = get_texture_color(r, r->texx, r->texy);
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		offset = y * win->size_line + x * (win->bpp / 8);
		*(unsigned int *)(data + offset) = color;
		y++;
	}
}

t_wall	*ft_get_texture(t_game *game, t_ray *r)
{
	if (r->side == 1)
	{
		if (r->raydir.y < 0)
			return (game->txt.n);
		else
			return (game->txt.s);
	}
	else
	{
		if (r->raydir.x < 0)
			return (game->txt.w);
		else
			return (game->txt.e);
	}
}
