#include "window.h"
#include "../../includes/main.h"
#include <stdlib.h>

/* ************************************************************************** */
/*                            Fonctions vecteur                               */
/* ************************************************************************** */

// Renvoie a - b
t_vec vec_sub(t_vec a, t_vec b)
{
    t_vec res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return (res);
}

// Renvoie le vecteur normalisé de a
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

/* ************************************************************************** */
/*                        Initialisation de la scène                          */
/* ************************************************************************** */

// Initialise les paramètres de la scène dans 'scene'
void init_scene(t_scene *scene)
{
    scene->win_width = 800;
    scene->win_height = 600;
    scene->camera.x = 2.5;
    scene->camera.y = 2.5;
    scene->camera.z = -5.0;
    scene->view_center.x = scene->camera.x;
    scene->view_center.y = scene->camera.y;
    scene->view_center.z = scene->camera.z + 1.0;
    scene->vp_height = 2.0;
    scene->vp_width = 2.6666;
    scene->lower_left.x = scene->view_center.x - (scene->vp_width / 2.0);
    scene->lower_left.y = scene->view_center.y - (scene->vp_height / 2.0);
    scene->lower_left.z = scene->view_center.z;
    scene->cube_min.x = 2.0;
    scene->cube_min.y = 2.0;
    scene->cube_min.z = 0.0;
    scene->cube_max.x = 3.0;
    scene->cube_max.y = 3.0;
    scene->cube_max.z = 1.0;
}

/* ************************************************************************** */
/*                      Calcul de la couleur d'un pixel                       */
/* ************************************************************************** */

// Calcule la couleur du pixel (x,y) en effectuant du raytracing sur le cube
int compute_pixel_color(int x, int y, t_scene *scene)
{
    t_uv uv;
    t_vec ray_dir;
    double t;
    int color;

    uv.u = (double)x / (scene->win_width - 1);
    uv.v = (double)y / (scene->win_height - 1);
    ray_dir = vec_normalize(vec_sub((t_vec){
            scene->lower_left.x + uv.u * scene->vp_width,
            scene->lower_left.y + uv.v * scene->vp_height,
            scene->lower_left.z}, scene->camera));
    if (intersect_cube(scene->camera, ray_dir, scene->cube_min, scene->cube_max, &t))
        color = 0xFFFFFF;
    else
        color = 0x000000;
    return (color);
}

/* ************************************************************************** */
/*                     Rendu des pixels dans l'image                        */
/* ************************************************************************** */

// Parcourt chaque pixel et y affecte une couleur calculée
void render_pixels(char *addr, int line_length, int bits_per_pixel, t_scene *scene)
{
    int x;
    int y;
    int index;
    int color;

    y = 0;
    while (y < scene->win_height)
    {
        x = 0;
        while (x < scene->win_width)
        {
            color = compute_pixel_color(x, y, scene);
            index = y * line_length + x * (bits_per_pixel / 8);
            *(unsigned int *)(addr + index) = color;
            x = x + 1;
        }
        y = y + 1;
    }
}

/* ************************************************************************** */
/*                         Rendu de la scène (raytracing)                     */
/* ************************************************************************** */

// Crée une image, rend la scène dedans et l'affiche dans la fenêtre
void render_scene(t_vars *vars)
{
    t_img image;

    image.img = mlx_new_image(vars->mlx, vars->scene.win_width,
            vars->scene.win_height);
    image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
            &image.line_length, &image.endian);
    render_pixels(image.addr, image.line_length,
            image.bits_per_pixel, &vars->scene);
    mlx_put_image_to_window(vars->mlx, vars->win, image.img, 0, 0);
    mlx_destroy_image(vars->mlx, image.img);
}

/* ************************************************************************** */
/*                         Mise à jour de la caméra                           */
/* ************************************************************************** */

/*
 * update_camera
 *
 * Met à jour la position de la caméra dans la structure scene selon
 * la touche pressée. On déplace la caméra sur l'axe X (gauche/droite)
 * et sur l'axe Z (se rapprocher/s'éloigner). L'axe Y reste constant.
 *
 * Paramètres :
 *   - scene : structure regroupant les paramètres de la scène.
 *   - keycode : code de la touche pressée.
 */
void update_camera(t_scene *scene, int keycode)
{
    double delta;

    delta = 0.2;
    if (keycode == 65361)
        scene->camera.x = scene->camera.x - delta;
    else if (keycode == 65363)
        scene->camera.x = scene->camera.x + delta;
    else if (keycode == 65362)
        scene->camera.z = scene->camera.z + delta;
    else if (keycode == 65364)
        scene->camera.z = scene->camera.z - delta;
    scene->view_center.x = scene->camera.x;
    scene->view_center.y = scene->camera.y;  /* Reste constant */
    scene->view_center.z = scene->camera.z + 1.0;
    scene->lower_left.x = scene->view_center.x - (scene->vp_width / 2.0);
    scene->lower_left.y = scene->view_center.y - (scene->vp_height / 2.0);
    scene->lower_left.z = scene->view_center.z;
}


/* ************************************************************************** */
/*                            Gestion du clavier                              */
/* ************************************************************************** */

// Met à jour la position de la caméra selon la touche pressée
int key_hook(int keycode, t_vars *vars)
{
    if (keycode == 65307)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    update_camera(&vars->scene, keycode);
    render_scene(vars);
    return (0);
}

int intersect_cube(t_vec origin, t_vec dir, t_vec box_min, t_vec box_max, double *t_out)
{
    t_bounds b;

    if (dir.x == 0)
    {
        if (origin.x < box_min.x || origin.x > box_max.x)
            return (0);
        b.tmin = -INFINITY;
        b.tmax = INFINITY;
    }
    else
    {
        b.tmin = (box_min.x - origin.x) / dir.x;
        b.tmax = (box_max.x - origin.x) / dir.x;
        if (b.tmin > b.tmax)
        {
            b.temp = b.tmin;
            b.tmin = b.tmax;
            b.tmax = b.temp;
        }
    }
    if (dir.y == 0)
    {
        if (origin.y < box_min.y || origin.y > box_max.y)
            return (0);
        b.tymin = -INFINITY;
        b.tymax = INFINITY;
    }
    else
    {
        b.tymin = (box_min.y - origin.y) / dir.y;
        b.tymax = (box_max.y - origin.y) / dir.y;
        if (b.tymin > b.tymax)
        {
            b.temp = b.tymin;
            b.tymin = b.tymax;
            b.tymax = b.temp;
        }
    }
    if (b.tmin > b.tymax || b.tymin > b.tmax)
        return (0);
    if (b.tymin > b.tmin)
        b.tmin = b.tymin;
    if (b.tymax < b.tmax)
        b.tmax = b.tymax;
    if (dir.z == 0)
    {
        if (origin.z < box_min.z || origin.z > box_max.z)
            return (0);
        b.tzmin = -INFINITY;
        b.tzmax = INFINITY;
    }
    else
    {
        b.tzmin = (box_min.z - origin.z) / dir.z;
        b.tzmax = (box_max.z - origin.z) / dir.z;
        if (b.tzmin > b.tzmax)
        {
            b.temp = b.tzmin;
            b.tzmin = b.tzmax;
            b.tzmax = b.temp;
        }
    }
    if (b.tmin > b.tzmax || b.tzmin > b.tmax)
        return (0);
    if (b.tzmin > b.tmin)
        b.tmin = b.tzmin;
    if (b.tzmax < b.tmax)
        b.tmax = b.tzmax;
    if (b.tmin < 0)
    {
        if (b.tmax < 0)
            return (0);
        else
            *t_out = b.tmax;
    }
    else
        *t_out = b.tmin;
    return (1);
}


int close_window(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return (0);
}


/* ************************************************************************** */
/*                   Initialisation de la fenêtre MLX                         */
/* ************************************************************************** */

// Initialise MLX, la fenêtre et la scène, installe les hooks et lance la boucle
int ft_window(void)
{
    t_vars vars;

    vars.mlx = mlx_init();
    if (!vars.mlx)
        return (1);
    vars.win = mlx_new_window(vars.mlx, 800, 600, "Cub3d Raytracing");
    if (!vars.win)
    {
        free(vars.mlx);
        return (1);
    }
    init_scene(&vars.scene);
    render_scene(&vars);
    mlx_hook(vars.win, 17, 0, (int (*)())close_window, &vars);
    mlx_hook(vars.win, 2, 1L<<0, (int (*)())key_hook, &vars);
    mlx_loop(vars.mlx);
    return (0);
}
