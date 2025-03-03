#include <../includes/main.h>

void	init_struct(t_game *game)
{
	game->fd = -1;
	game->map.lenght = 0;
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
	game->texture.east_texture = NULL;
	game->texture.north_texture = NULL;
	game->texture.south_texture = NULL;
	game->texture.west_texture = NULL;
}
