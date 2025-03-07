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

int	key_hook(int keycode, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (keycode == 65307) // Escape
		close_window(env);
	if (keycode == 65361) // flèche gauche
		env->game.plr.dir = turnv(env->game.plr.dir, -RADTURN);
	else if (keycode == 65363) // flèche droite
		env->game.plr.dir = turnv(env->game.plr.dir, RADTURN);
	if(keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		env->game.plr.pos = ft_move(&env->game.plr.pos, &env->game.plr.dir, &env->game, keycode);
	ft_setplan(&env->game.plr, FOV);
	ft_draw(&env->game, &env->win);
	return (0);
}

t_vec ft_move(t_vec *pos, t_vec *dir, t_game *game, int keycode)
{
    t_vec newpos;

	newpos.x = 0;
	if (keycode == 119) // 'w' : avancer
	{
		newpos.x = pos->x + (0.001 + dir->x) * SPEED;
		newpos.y = pos->y + (0.001 + dir->y) * SPEED;
	}
	else if (keycode == 115) // 's' : reculer
	{
		newpos.x = pos->x - (0.001 + dir->x) * SPEED;
		newpos.y = pos->y - (0.001 + dir->y) * SPEED;
	}
	else if (keycode == 97)  // 'a' : strafe gauche
	{
		newpos.x = pos->x + (0.001 + dir->y) * SPEED;
		newpos.y = pos->y - (0.001 + dir->x) * SPEED;
	}
	else if (keycode == 100) // 'd' : strafe droite
	{
		newpos.x = pos->x - (0.001 + dir->y) * SPEED;
		newpos.y = pos->y + (0.001 + dir->x) * SPEED;
	}
	(void)keycode;
	return(ft_testpos(newpos, pos, game));
}


t_vec	ft_testpos(t_vec newpos, t_vec *pos, t_game *game)
{
	t_vec pos_try;

	if (game->map.map[(int)newpos.x][(int)newpos.y] != '1')
		return newpos;
	pos_try.x = newpos.x;
	pos_try.y = pos->y;
	if (game->map.map[(int)pos_try.x][(int)pos_try.y] != '1')
		return pos_try;
	pos_try.x = pos->x;
	pos_try.y = newpos.y;
	if (game->map.map[(int)pos_try.x][(int)pos_try.y] != '1')
		return pos_try;
	return *pos;

}

int	close_window(t_env *env)
{
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
				pos->x = i + 0.5;
				pos->y = j + 0.5;
				if(map[i][j] == 'E')
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
	ft_findp(game->map.map,&plr->pos);
	plr->dir.y = 0;
	plr->dir.x = 0;
	if(game->map.map[(int)plr->pos.x][(int)plr->pos.y] == 'N')
		plr->dir.y = 1;
	else if(game->map.map[(int)plr->pos.x][(int)plr->pos.y] == 'S')
		plr->dir.y = -1;
	else if(game->map.map[(int)plr->pos.x][(int)plr->pos.y] == 'W')
		plr->dir.x = -1;
	else
		plr->dir.x = 1;
	ft_setplan(plr,FOV);
}

void	ft_setposmap(t_ray *r)
{
	r->mapX = (int)r->rayDir.x;
	r->mapY = (int)r->rayDir.y;
}

void	ft_setSideDist(t_ray *r, double posX, double posY)
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

void	ft_testhit(t_ray *r, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->sideDist.x < r->sideDist.y)
		{
			r->sideDist.x += r->deltaDist.x;  // On "saute" à la prochaine frontière verticale
			r->mapX += r->stepX;            // On avance d'une case sur l'axe X
			r->side = 0;                 // Indique que le saut a été effectué en X (mur vertical)
		}
		else
		{
			r->sideDist.y += r->deltaDist.y;  // On "saute" à la prochaine frontière horizontale
			r->mapY += r->stepY;            // On avance d'une case sur l'axe Y
			r->side = 1;                 // Indique que le saut a été effectué en Y (mur horizontal)
		}
		if (r->mapY < 0 || r->mapY >= ft_tablen(game->map.map) ||
			r->mapX < 0 || r->mapX >= (int)ft_strlen(game->map.map[r->mapY]))
				hit = 1;
		if (game->map.map[r->mapX][r->mapY] == '1')
			hit = 1;
	}
	if (r->side == 0)
		r->perpWallDist = r->sideDist.x - r->deltaDist.x;
	else
		r->perpWallDist = r->sideDist.y - r->deltaDist.y;
}


t_vec	ft_onecol(int x, t_player plr)
{
	double camX;
	t_vec rayDir;

	camX = 2*x /(double)SCREENX -1;
	rayDir.x =  plr.dir.x + plr.plane.x * camX;
	rayDir.y =  plr.dir.y + plr.plane.y * camX;
	return(rayDir);
}

void	ft_allcol(t_game *game, int *size_line, int *bpp, char *data)
{
	int		x;
	t_ray	r;
	int		lineHeight;

	x = 0;
	while(x < SCREENX)
	{
		r.rayDir = ft_onecol(x, game->plr);
		r.mapX = (int)game->plr.pos.x;
		r.mapY = (int)game->plr.pos.y;
		ft_setdelta(&r);
		ft_setSideDist(&r, game->plr.pos.x, game->plr.pos.y);
		ft_testhit(&r, game);
		lineHeight = (int)(SCREENY / r.perpWallDist);
		ft_lim(&r, lineHeight, size_line, bpp, data, x);
		x++;
	}
}

void	ft_draw(t_game *game, t_window *win)
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*data;

	win->img = mlx_new_image(win->mlx, SCREENX, SCREENY);
	if (!win->img)
		return;
	data = mlx_get_data_addr(win->img, &bpp, &size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(win->mlx, win->img);
		return;
	}
	ft_draw_background(game, data, size_line);
	ft_allcol(game, &size_line, &bpp, data);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	mlx_destroy_image(win->mlx, win->img);
}

void	ft_lim(t_ray *r, int lh, int *size_line, int *bpp, char *data, int x)
{
	int	Dstart;
	int	Dend;
	int	y;
	int	offset;

	Dstart = -lh / 2 + SCREENY / 2;
	Dend = lh / 2 + SCREENY / 2;
	r->color = COLOR;
	if(Dstart < 0)
		Dstart = 0;
	if(Dend >= SCREENY)
		Dend = SCREENY - 1;
	if (r->side == 1)
		r->color = (r->color >> 1) & 8355711;
	y = Dstart;
	while(y < Dend)
	{
		offset = y * *size_line + x * (*bpp / 8);
		*(unsigned int *)(data + offset) = r->color;
		y++;
	}
}

void	ft_setdelta(t_ray *r)
{
	if (r->rayDir.x == 0)
		r->deltaDist.x = 1e30;  // Valeur très élevée pour éviter la division par zéro
	else
		r->deltaDist.x = fabs(1 / r->rayDir.x);

	if (r->rayDir.y == 0)
		r->deltaDist.y = 1e30;
	else
		r->deltaDist.y = fabs(1 / r->rayDir.y);
}

// #include <stdio.h>

// int mouse_motion_hook(int x, int y, void *param)
// {
//     // static unsigned long last_time = 0;
//     // unsigned long current_time = get_ticks(); // Fonction qui renvoie le temps en ms
//     t_env *env = (t_env *)param;

//     // Ne traiter l'événement que si 20 ms se sont écoulées
//     // if (current_time - last_time < 20)
//     //     return (0);
//     (void)y;
//     // last_time = current_time;
//     if (x < SCREENX / 3)
//         env->game.plr.dir = turnv(env->game.plr.dir, -RADTURN * x / 100);
//     else if (x > SCREENX * (2 / 3))
//         env->game.plr.dir = turnv(env->game.plr.dir, RADTURN);
//     ft_setplan(&env->game.plr, FOV);
//     ft_draw(&env->game, &env->win);
//     return (0);
// }

int update(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->game.plr.dir = turnv(env->game.plr.dir, RADTURN * ( -((double)env->mouse) / 10.0 ));
	ft_setplan(&env->game.plr, FOV);
	ft_draw(&env->game, &env->win);

	return (0);
}



int	mouse_motion_hook(int x, int y, void *param)
{
	t_env	*env;

	(void)y;
	env = (t_env *)param;
	int threshold = SCREENX / 5;  // marge autour du centre
	int center = SCREENX / 2;

	if (x < threshold)
		env->mouse = 2;         // Extrême gauche
	else if (x > SCREENX - threshold)
		env->mouse = -2;        // Extrême droite
	else if (x < center - threshold * 0.4)
		env->mouse = 1;         // Gauche modéré
	else if (x > center + threshold * 0.4)
		env->mouse = -1;        // Droite modérée
	else
		env->mouse = 0;         // Au centre, pas de rotation

	return (0);
}

void	ft_setplan(t_player *plr, double planeLength)
{
	plr->plane.x = -plr->dir.y * planeLength;
	plr->plane.y =  plr->dir.x * planeLength;
}

t_vec turnv(t_vec v, double rad)
{
	t_vec	rotated;
	rotated.x = v.x * cos(rad) - v.y * sin(rad);
	rotated.y = v.x * sin(rad) + v.y * cos(rad);
	return (rotated);
}


int	ft_window(t_game *game)
{
	t_env env;

	// Initialisation de MLX et de la fenêtre
	env.win.mlx = mlx_init();
	if (!env.win.mlx)
		return (1);
	// Copie du jeu et initialisation du joueur
	env.game = *game;
	ft_initp(&env.game, &env.game.plr);
	env.mouse = 0;
	env.win.win = mlx_new_window(env.win.mlx, SCREENX, SCREENY, "Cub3d Raytracing");
	if (!env.win.win)
	{
		free(env.win.mlx);
		free_ressource(game);
		return (1);
	}
	ft_draw(&env.game, &env.win);
	// Associer notre structure à MLX
	mlx_hook(env.win.win, 17, 0, (int (*)())close_window, &env);
	mlx_hook(env.win.win, 2, 1L<<0, key_hook, &env); // Passer &env ici
	mlx_hook(env.win.win, MotionNotify, PointerMotionMask, mouse_motion_hook, &env);
	mlx_loop_hook(env.win.mlx, update, &env);
	mlx_loop(env.win.mlx);
	return (0);
}

