/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:30:00 by gtraiman          #+#    #+#             */
/*   Updated: 2025/03/07 00:00:52 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "../../includes/main.h"
#include <stdlib.h>

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	key_hook(int keycode, void	*param)
{
	t_env	*env;

	env = (t_env *)param;
	if (keycode == 65307)
		close_window(env);
	if (keycode == 65361)
		env->game.plr.dir = turnv(env->game.plr.dir, -RADTURN);
	else if (keycode == 65363)
		env->game.plr.dir = turnv(env->game.plr.dir, RADTURN);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		env->game.plr.pos = ft_move(&env->game.plr.pos,
				&env->game.plr.dir, &env->game, keycode);
	ft_setplan(&env->game.plr, FOV);
	ft_draw(&env->game, &env->win);
	return (0);
}

t_vec	ft_move(t_vec *pos, t_vec *dir, t_game *game, int keycode)
{
	t_vec	newpos;

	newpos.x = 0;
	if (keycode == 119)
	{
		newpos.x = pos->x + (0.001 + dir->x) * SPEED;
		newpos.y = pos->y + (0.001 + dir->y) * SPEED;
	}
	else if (keycode == 115)
	{
		newpos.x = pos->x - (0.001 + dir->x) * SPEED;
		newpos.y = pos->y - (0.001 + dir->y) * SPEED;
	}
	else if (keycode == 97)
	{
		newpos.x = pos->x + (0.001 + dir->y) * SPEED;
		newpos.y = pos->y - (0.001 + dir->x) * SPEED;
	}
	else if (keycode == 100)
	{
		newpos.x = pos->x - (0.001 + dir->y) * SPEED;
		newpos.y = pos->y + (0.001 + dir->x) * SPEED;
	}
	(void)keycode;
	return (ft_testpos(newpos, pos, game));
}

t_vec	ft_testpos(t_vec newpos, t_vec *pos, t_game *game)
{
	t_vec	pos_try;

	if (game->map.map[(int)newpos.y][(int)newpos.x] != '1')
		if (game->map.map[(int)newpos.y][(int)pos->x] != '1')
			if (game->map.map[(int)pos->y][(int)pos->x] != '1')
				return (newpos);
	pos_try.x = newpos.x;
	pos_try.y = pos->y;
	if (game->map.map[(int)pos_try.y][(int)pos_try.x] != '1')
		return (pos_try);
	pos_try.x = pos->x;
	pos_try.y = newpos.y;
	if (game->map.map[(int)pos_try.y][(int)pos_try.x] != '1')
		return (pos_try);
	return (*pos);
}

int	close_window(t_env *env)
{
	ft_free_textures(&env->game, &env->win);
	free_ressource(&env->game);
	mlx_destroy_window(env->win.mlx, env->win.win);
	mlx_destroy_display(env->win.mlx);
	free(env->win.mlx);
	exit(0);
	return (0);
}

void	ft_findp(char **map, t_vec *pos)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_cins("NESW", map[i][j]) == 1)
			{
				pos->y = i + 0.5;
				pos->x = j + 0.5;
				if (map[i][j] == 'E')
					pos->x--;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_initp(t_game *game, t_player *plr)
{
	ft_findp(game->map.map, &plr->pos);
	plr->dir.y = 0;
	plr->dir.x = 0;
	if (game->map.map[(int)plr->pos.y][(int)plr->pos.x] == 'N')
		plr->dir.y = 1;
	else if (game->map.map[(int)plr->pos.y][(int)plr->pos.x] == 'S')
		plr->dir.y = -1;
	else if (game->map.map[(int)plr->pos.y][(int)plr->pos.x] == 'W')
		plr->dir.x = -1;
	else
		plr->dir.x = 1;
	ft_setplan(plr, FOV);
}

void	ft_setposmap(t_ray *r)
{
	r->mapX = (int)r->rayDir.x;
	r->mapY = (int)r->rayDir.y;
}

void	ft_setsidedist(t_ray *r, double posX, double posY)
{
	if (r->rayDir.x < 0)
	{
		r->stepX = -1;
		r->sideDist.x = (posX - r->mapX) * r->deltaDist.x;
	}
	else
	{
		r->stepX = 1;
		r->sideDist.x = (r->mapX + 1.0 - posX) * r->deltaDist.x;
	}
	if (r->rayDir.y < 0)
	{
		r->stepY = -1;
		r->sideDist.y = (posY - r->mapY) * r->deltaDist.y;
	}
	else
	{
		r->stepY = 1;
		r->sideDist.y = (r->mapY + 1.0 - posY) * r->deltaDist.y;
	}
}

void	ft_testhit(t_ray *r, t_game *game, int hit)
{
	while (hit == 0)
	{
		if (r->sideDist.x < r->sideDist.y)
		{
			r->sideDist.x += r->deltaDist.x;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDist.y += r->deltaDist.y;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (r->mapY < 0 || r->mapY >= ft_tablen(game->map.map)
			|| r->mapX < 0 || r->mapX >= (int)ft_strlen(game->map.map[r->mapY]))
				hit = 1;
		if (game->map.map[r->mapY][r->mapX] == '1')
			hit = 1;
	}
	if (r->side == 0)
		r->perpWallDist = r->sideDist.x - r->deltaDist.x;
	else
		r->perpWallDist = r->sideDist.y - r->deltaDist.y;
}

t_vec	ft_onecol(int x, t_player plr)
{
	double	camx;
	t_vec	raydir;

	camx = 2 * x / (double)SCREENX - 1;
	raydir.x = plr.dir.x + plr.plane.x * camx;
	raydir.y = plr.dir.y + plr.plane.y * camx;
	return (raydir);
}

void	ft_init_ray(t_ray *r, t_game *game, int x)
{
	r->rayDir = ft_onecol(x, game->plr);
	r->mapX = (int)game->plr.pos.x;
	r->mapY = (int)game->plr.pos.y;
	ft_setdelta(r);
	ft_setsidedist(r, game->plr.pos.x, game->plr.pos.y);
	ft_testhit(r, game, 0);
	r->lh = (int)(SCREENY / r->perpWallDist);
	r->Ds = -r->lh / 2 + SCREENY / 2;
	if (r->Ds < 0)
		r->Ds = 0;
	r->De = r->lh / 2 + SCREENY / 2;
	if (r->De >= SCREENY)
		r->De = SCREENY - 1;
	r->texture = ft_get_texture(game, r);
}

void	ft_allcol(t_game *game, char *data, t_window *win)
{
	int			x;
	t_ray		r;

	x = 0;
	while (x < SCREENX)
	{
		ft_init_ray(&r, game, x);
		calculate_wallx(&r, &game->plr);
		calculate_texx(&r, r.texture->width);
		draw_textured_wall(&r, x, data, win);
		x++;
	}
}

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

void	calculate_wallx(t_ray *r, t_player *plr)
{
	if (r->side == 0)
		r->wallX = plr->pos.y + r->perpWallDist * r->rayDir.y;
	else
		r->wallX = plr->pos.x + r->perpWallDist * r->rayDir.x;
	r->wallX -= floor(r->wallX);
}

void	calculate_texx(t_ray *r, int texWidth)
{
	r->texX = (int)(r->wallX * (double)texWidth);
	if (r->side == 0 && r->rayDir.x > 0)
		r->texX = texWidth - r->texX - 1;
	if (r->side == 1 && r->rayDir.y < 0)
		r->texX = texWidth - r->texX - 1;
}

int	get_texture_color(t_ray *r, int texX, int texY)
{
	int	offset;

	if (!r->texture)
	{
		printf("Error: Texture is NULL\n");
		return (0);
	}
	if (!r->texture->p)
	{
		printf("Error: Texture data is NULL\n");
		return (0);
	}
	if (texX < 0 || texX >= r->texture->width || texY < 0
		|| texY >= r->texture->height)
	{
		printf("Error: Texture coordinates out of bounds\n");
		return (0);
	}
	offset = texY * r->texture->size_line + texX * (r->texture->bpp / 8);
	if (offset < 0 || offset >= r->texture->size_line * r->texture->height)
	{
		printf("Error: Invalid offset (offset=%d)\n", offset);
		return (0);
	}
	return (*(int *)(r->texture->p + offset));
}

void	draw_textured_wall(t_ray *r, int x, char *data, t_window *win)
{
	int			y;
	double		step;
	unsigned int				color;
	int			offset;

	step = 1.0 * r->texture->height / r->lh;
	r->texPos = (r->Ds - SCREENY / 2 + r->lh / 2) * step;
	y = r->Ds;
	while (y < r->De)
	{
		r->texY = (int)r->texPos & (r->texture->height - 1);
		r->texPos += step;
		color = get_texture_color(r, r->texX, r->texY);
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
		if (r->rayDir.y < 0)
			return (game->txt.n);
		else
			return (game->txt.s);
	}
	else
	{
		if (r->rayDir.x < 0)
			return (game->txt.w);
		else
			return (game->txt.e);
	}
}

void	load_textures(t_env *env, t_game *game, t_window *win)
{
	game->txt.n->img = mlx_xpm_file_to_image(win->mlx, game->txt.n->c,
			&game->txt.n->width, &game->txt.n->height);
	if (game->txt.n->img)
		game->txt.n->p = mlx_get_data_addr(game->txt.n->img, &game->txt.n->bpp,
				&game->txt.n->size_line, &game->txt.n->endian);
	game->txt.s->img = mlx_xpm_file_to_image(win->mlx,
			game->txt.s->c, &game->txt.s->width, &game->txt.s->height);
	if (game->txt.s->img)
		game->txt.s->p = mlx_get_data_addr(game->txt.s->img, &game->txt.s->bpp,
				&game->txt.s->size_line, &game->txt.s->endian);
	game->txt.e->img = mlx_xpm_file_to_image(win->mlx,
			game->txt.e->c, &game->txt.e->width, &game->txt.e->height);
	if (game->txt.e->img)
		game->txt.e->p = mlx_get_data_addr(game->txt.e->img, &game->txt.e->bpp,
				&game->txt.e->size_line, &game->txt.e->endian);
	game->txt.w->img = mlx_xpm_file_to_image(win->mlx,
			game->txt.w->c, &game->txt.w->width, &game->txt.w->height);
	if (game->txt.w->img)
		game->txt.w->p = mlx_get_data_addr(game->txt.w->img, &game->txt.w->bpp,
				&game->txt.w->size_line, &game->txt.w->endian);
	if (!game->txt.n->img || !game->txt.s->img
		|| !game->txt.e->img || !game->txt.w->img)
		return (printf("Error: Failed to load textures\n"),
			close_window(env), (void)env);
}

void	ft_free_textures(t_game *game, t_window *win)
{
	if (game->txt.n->img)
		mlx_destroy_image(win->mlx, game->txt.n->img);
	if (game->txt.s->img)
		mlx_destroy_image(win->mlx, game->txt.s->img);
	if (game->txt.e->img)
		mlx_destroy_image(win->mlx, game->txt.e->img);
	if (game->txt.w->img)
		mlx_destroy_image(win->mlx, game->txt.w->img);
}

void	ft_setdelta(t_ray *r)
{
	if (r->rayDir.x == 0)
		r->deltaDist.x = 1e30;
	else
		r->deltaDist.x = fabs(1 / r->rayDir.x);
	if (r->rayDir.y == 0)
		r->deltaDist.y = 1e30;
	else
		r->deltaDist.y = fabs(1 / r->rayDir.y);
}

int	update(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->game.plr.dir = turnv(env->game.plr.dir,
			RADTURN *(-((double)env->mouse) / 10.0));
	ft_setplan(&env->game.plr, FOV);
	ft_draw(&env->game, &env->win);
	return (0);
}

int	mouse_motion_hook(int x, int y, void	*param)
{
	t_env	*env;

	(void)y;
	env = (t_env *)param;
	if (x < SCREENX / 5 * 0.5)
		env->mouse = 8;
	else if (x > SCREENX - SCREENX / 5 * 0.5)
		env->mouse = -8;
	else if (x < SCREENX / (5 * 1.3))
		env->mouse = 4;
	else if (x > SCREENX - SCREENX / 5 * 1.3)
		env->mouse = -4;
	else if (x < SCREENX / 2 - SCREENX / 5 * 0.6)
		env->mouse = 2;
	else if (x > SCREENX / 2 + SCREENX / 5 * 0.6)
		env->mouse = -2;
	else if (x < SCREENX / 2 - SCREENX / 5 * 0.3)
		env->mouse = 1;
	else if (x > SCREENX / 2 + SCREENX / 5 * 0.3)
		env->mouse = -1;
	else
		env->mouse = 0;
	return (0);
}

void	ft_setplan(t_player *plr, double planeLength)
{
	plr->plane.x = -plr->dir.y * planeLength;
	plr->plane.y = plr->dir.x * planeLength;
}

t_vec	turnv(t_vec v, double rad)
{
	t_vec	rotated;

	rotated.x = v.x * cos(rad) - v.y * sin(rad);
	rotated.y = v.x * sin(rad) + v.y * cos(rad);
	return (rotated);
}

int	ft_window(t_game *game)
{
	t_env	env;

	env.win.mlx = mlx_init();
	if (!env.win.mlx)
		return (1);
	env.game = *game;
	ft_initp(&env.game, &env.game.plr);
	env.mouse = 0;
	env.win.win = mlx_new_window(env.win.mlx,
			SCREENX, SCREENY, "Cub3d Raytracing");
	if (!env.win.win)
	{
		free(env.win.mlx);
		free_ressource(game);
		return (1);
	}
	load_textures(&env, &env.game, &env.win);
	ft_draw(&env.game, &env.win);
	mlx_hook(env.win.win, 17, 0, (int (*)())close_window, &env);
	mlx_hook(env.win.win, 2, 1L << 0, key_hook, &env);
	mlx_hook(env.win.win, MotionNotify, 1L << 6, mouse_motion_hook, &env);
	mlx_loop_hook(env.win.mlx, update, &env);
	mlx_loop(env.win.mlx);
	return (0);
}

