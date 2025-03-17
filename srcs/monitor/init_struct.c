#include <../includes/main.h>

void init_struct(t_game *game)
{
    game->fd = -1;
    game->map.lenght = 0;
    game->map.row = 0;
    game->texture.line_save = NULL;
    game->map.map = NULL;
    game->map.lenght_index = 0;
    game->texture.r = -1;
    game->texture.g = -1;
    game->texture.b = -1;
    game->texture.count = 0;
    game->texture.count_player = 0;
    game->texture.roof_color = -1;
    game->texture.ground_color = -1;
    game->texture.east = malloc(sizeof(t_wall));
    game->texture.north = malloc(sizeof(t_wall));
    game->texture.south = malloc(sizeof(t_wall));
    game->texture.west = malloc(sizeof(t_wall));
    if (!game->texture.east || !game->texture.north || !game->texture.south || !game->texture.west)
        return(printf("Error: Memory allocation failed\n"), exit(1));
    game->texture.east->c = NULL;
    game->texture.north->c = NULL;
    game->texture.south->c = NULL;
    game->texture.west->c = NULL;
}

void free_ressource(t_game *game)
{
    close_fd(game);

    if (game->texture.east)
    {
        if (game->texture.east->c)
            free(game->texture.east->c);
        free(game->texture.east);
    }
    if (game->texture.north)
    {
        if (game->texture.north->c)
            free(game->texture.north->c);
        free(game->texture.north);
    }
    if (game->texture.south)
    {
        if (game->texture.south->c)
            free(game->texture.south->c);
        free(game->texture.south);
    }
    if (game->texture.west)
    {
        if (game->texture.west->c)
            free(game->texture.west->c);
        free(game->texture.west);
    }
    if (game->map.map)
        dest_free(game->map.map);
    game->texture.east = NULL;
    game->texture.north = NULL;
    game->texture.south = NULL;
    game->texture.west = NULL;
}
