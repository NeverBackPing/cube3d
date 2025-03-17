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

	if (game->map.map[(int)newpos.y][(int)newpos.x] != '1')
		return newpos;
	pos_try.x = newpos.x;
	pos_try.y = pos->y;
	if (game->map.map[(int)pos_try.y][(int)pos_try.x] != '1')
		return pos_try;
	pos_try.x = pos->x;
	pos_try.y = newpos.y;
	if (game->map.map[(int)pos_try.y][(int)pos_try.x] != '1')
		return pos_try;
	return *pos;

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
	if(game->map.map[(int)plr->pos.y][(int)plr->pos.x] == 'N')
		plr->dir.y = 1;
	else if(game->map.map[(int)plr->pos.y][(int)plr->pos.x] == 'S')
		plr->dir.y = -1;
	else if(game->map.map[(int)plr->pos.y][(int)plr->pos.x] == 'W')
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

void	ft_testhit(t_ray *r, t_game *game, int hit)
{
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
	double camX;
	t_vec rayDir;

	camX = 2*x /(double)SCREENX -1;
	rayDir.x =  plr.dir.x + plr.plane.x * camX;
	rayDir.y =  plr.dir.y + plr.plane.y * camX;
	return(rayDir);
}

void ft_init_ray(t_ray *r, t_game *game, int x)
{
    r->rayDir = ft_onecol(x, game->plr);
    r->mapX = (int)game->plr.pos.x;
    r->mapY = (int)game->plr.pos.y;
    ft_setdelta(r);
    ft_setSideDist(r, game->plr.pos.x, game->plr.pos.y);
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

void ft_allcol(t_game *game, char *data, t_window *win)
{
    int x;
    t_ray r;

    x = 0;

    while (x < SCREENX)
    {
        ft_init_ray(&r, game, x);
        calculate_wallX(&r, &game->plr);
        calculate_texX(&r, r.texture->width);
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
		return;
	data = mlx_get_data_addr(win->img, &win->bpp, &win->size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(win->mlx, win->img);
		return;
	}
	ft_draw_background(game, data, win->size_line);
	ft_allcol(game, data, win);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	draw_minimap(game, data, win, win->size_line);
	mlx_destroy_image(win->mlx, win->img);
}

void calculate_wallX(t_ray *r, t_player *plr)
{
    if (r->side == 0)
        r->wallX = plr->pos.y + r->perpWallDist * r->rayDir.y;
    else
        r->wallX = plr->pos.x + r->perpWallDist * r->rayDir.x;
    r->wallX -= floor(r->wallX);
}

void calculate_texX(t_ray *r, int texWidth)
{
    r->texX = (int)(r->wallX * (double)texWidth);
    if (r->side == 0 && r->rayDir.x > 0)
        r->texX = texWidth - r->texX - 1;
    if (r->side == 1 && r->rayDir.y < 0)
        r->texX = texWidth - r->texX - 1;
}

// int get_texture_color(t_ray *r, int texX, int texY)
// {
//     int offset;

//     if (!r->texture || !r->texture->p)
//         return 0;
//     if (texX < 0 || texX >= r->texture->width || texY < 0 || texY >= r->texture->height)
//         return 0;
//     offset = texY * r->texture->size_line + texX * (r->texture->bpp / 8);
//     return *(int *)(r->texture->p + offset);
// }
int get_texture_color(t_ray *r, int texX, int texY)
{
    int offset;

    if (!r->texture)
    {
        printf("Error: Texture is NULL\n");
        return 0;
    }

    if (!r->texture->p)
    {
        printf("Error: Texture data is NULL\n");
        return 0;
    }

    // Vérifiez que texX et texY sont dans les limites de la texture
    if (texX < 0 || texX >= r->texture->width || texY < 0 || texY >= r->texture->height)
    {
        printf("Error: Texture coordinates out of bounds (texX=%d, texY=%d)\n", texX, texY);
        return 0;
    }

    offset = texY * r->texture->size_line + texX * (r->texture->bpp / 8);

    // Vérifiez que l'offset est dans les limites de la texture
    if (offset < 0 || offset >= r->texture->size_line * r->texture->height)
    {
        printf("Error: Invalid offset (offset=%d)\n", offset);
        return 0;
    }

    return *(int *)(r->texture->p + offset);
}

void draw_textured_wall(t_ray *r, int x, char *data, t_window *win)
{
    int y;
    double step;
    unsigned int color;
    int offset;

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

t_wall *ft_get_texture(t_game *game, t_ray *r)
{
    if (r->side == 1)
    {
        if (r->rayDir.y < 0)
            return game->texture.north;
        else
            return game->texture.south;
    }
    else
    {
        if (r->rayDir.x < 0)
            return game->texture.west;
        else
            return game->texture.east;
    }
}

void load_textures(t_env *env, t_game *game, t_window *win)
{
    free(game->texture.south->c);
    game->texture.south->c = ft_strdup("./sprites/image2.xpm");
    free(game->texture.north->c);
    game->texture.north->c = ft_strdup("./sprites/image2.xpm");
    free(game->texture.west->c);
    game->texture.west->c = ft_strdup("./sprites/image2.xpm");
    free(game->texture.east->c);
    game->texture.east->c = ft_strdup("./sprites/image2.xpm");
    game->texture.north->img = mlx_xpm_file_to_image(win->mlx, game->texture.north->c, &game->texture.north->width, &game->texture.north->height);
    if (game->texture.north->img)
        game->texture.north->p = mlx_get_data_addr(game->texture.north->img, &game->texture.north->bpp, &game->texture.north->size_line, &game->texture.north->endian);
    game->texture.south->img = mlx_xpm_file_to_image(win->mlx, game->texture.south->c, &game->texture.south->width, &game->texture.south->height);
    if (game->texture.south->img)
        game->texture.south->p = mlx_get_data_addr(game->texture.south->img, &game->texture.south->bpp, &game->texture.south->size_line, &game->texture.south->endian);
    game->texture.east->img = mlx_xpm_file_to_image(win->mlx, game->texture.east->c, &game->texture.east->width, &game->texture.east->height);
    if (game->texture.east->img)
        game->texture.east->p = mlx_get_data_addr(game->texture.east->img, &game->texture.east->bpp, &game->texture.east->size_line, &game->texture.east->endian);
    game->texture.west->img = mlx_xpm_file_to_image(win->mlx, game->texture.west->c, &game->texture.west->width, &game->texture.west->height);
    if (game->texture.west->img)
        game->texture.west->p = mlx_get_data_addr(game->texture.west->img, &game->texture.west->bpp, &game->texture.west->size_line, &game->texture.west->endian);
    if (!game->texture.north->img || !game->texture.south->img || !game->texture.east->img || !game->texture.west->img)
    {
        printf("Error: Failed to load textures\n");
        close_window(env);
    }
}


void ft_free_textures(t_game *game, t_window *win)
{
    if (game->texture.north->img)
        	mlx_destroy_image(win->mlx, game->texture.north->img);
    if (game->texture.south->img)
       		mlx_destroy_image(win->mlx, game->texture.south->img);
    if (game->texture.east->img)
        	mlx_destroy_image(win->mlx, game->texture.east->img);
    if (game->texture.west->img)
    		mlx_destroy_image(win->mlx, game->texture.west->img);
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
	load_textures(&env, &env.game, &env.win);
	ft_draw(&env.game, &env.win);
	// Associer notre structure à MLX
	mlx_hook(env.win.win, 17, 0, (int (*)())close_window, &env);
	mlx_hook(env.win.win, 2, 1L<<0, key_hook, &env); // Passer &env ici
	mlx_hook(env.win.win, MotionNotify, PointerMotionMask, mouse_motion_hook, &env);
	mlx_loop_hook(env.win.mlx, update, &env);
	mlx_loop(env.win.mlx);
	return (0);
}

