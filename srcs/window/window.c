#include "window.h"
#include "../../includes/main.h"
#include <stdlib.h>

t_vec vec_sub(t_vec a, t_vec b)
{
    t_vec res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return (res);
}

t_vec vec_normalize(t_vec a)
{
    double len;
    t_vec res;

    len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    if (len == 0)
    {
        res.x = 0;
        res.y = 0;
        res.z = 0;
    }
    else
    {
        res.x = a.x / len;
        res.y = a.y / len;
        res.z = a.z / len;
    }
    return (res);
}


int key_hook(int keycode, t_window *vars, t_player *plr)
{
    if (keycode == 65307)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    if (keycode == 65361) //G
        plr->dir = turnv(plr->dir,RADTURN);
    else if (keycode == 65363) //D
        plr->dir = turnv(plr->dir,-RADTURN);
    // else if (keycode == 65362) //DV
    // else if (keycode == 65364) //DR
    return (0);
}


int close_window(t_window *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return (0);
}

int *ft_findp(char **map)
{
    int i;
    int j;
    int *tab;

    i = 0;
    tab = malloc(2 * sizeof(int));
    if (!tab)
        return (NULL);
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (ft_cins("NESW", map[i][j]) == 1)
            {
                tab[0] = i;
                tab[1] = j;
                return (tab);
            }
            j++;
        }
        i++;
    }
    free(tab);
    return (NULL);
}

void ft_initp(t_game *game, t_player *plr)
{
    plr->pos.x = ft_findp(game->map.map)[0];
    plr->pos.y = ft_findp(game->map.map)[1];
    plr->dir.y = 0;
    plr->dir.x = 0;
    if(game->map.map[(int)plr->pos.x][(int)plr->pos.y] == 'N')
        plr->dir.y = 1;
    if(game->map.map[(int)plr->pos.x][(int)plr->pos.y] == 'S')
        plr->dir.y = -1;
    if(game->map.map[(int)plr->pos.x][(int)plr->pos.y] == 'W')
        plr->dir.x = -1;
    else
        plr->dir.x = 1;
    ft_setplan(plr,FOV);
}
void ft_setposmap(t_ray *r)
{
    r->mapX = (int)r->rayDir.x;
    r->mapY = (int)r->rayDir.y;
}
void ft_setSideDist(t_ray *r, double posX, double posY)
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

void    ft_onecol(int x)
{
    double camX;

    camX = 2*x /(double)SCREENX -1;
    
    
}

void ft_allcol(t_game *game)
{
    int x = 0;

    while(x < SCREENX)
    {
        ft_onecol(int x);
    }
}


void ft_setdelta(t_ray *r)
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


void ft_setplan(t_player *plr, double planeLength)
{
    plr->plane.x = -plr->dir.y * planeLength;
    plr->plane.y =  plr->dir.x * planeLength;
    plr->plane.z = 0;
}

t_vec turnv(t_vec v, double rad)
{
    t_vec rotated;
    rotated.x = v.x * cos(rad) - v.y * sin(rad);
    rotated.y = v.x * sin(rad) + v.y * cos(rad);
    rotated.z = v.z;
    return rotated;
}

int ft_window(t_game *game)
{
    t_window vars;

    vars.mlx = mlx_init();
    if (!vars.mlx)
        return (1);
    ft_initp(game,&game->plr);
    vars.win = mlx_new_window(vars.mlx, SCREENX, SCREENY, "Cub3d Raytracing");
    if (!vars.win)
    {
        free(vars.mlx);
        free_ressource(game);
        return (1);
    }
    mlx_hook(vars.win, 17, 0, (int (*)())close_window, &vars);
    mlx_hook(vars.win, 2, 1L<<0, (int (*)())key_hook, &vars);
    mlx_loop(vars.mlx);
    return (0);
}
