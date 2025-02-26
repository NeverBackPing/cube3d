#include "checkmap.h"

void	open_fd(t_game *game, char *filename)
{
	game->fd = -1;
	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
	{
		printf("\033[0;31mError\033[0m: Sorry I can't open the fd\n");
		exit(0);
	}
}

void	get_map(t_game *game, char *filename)
{
	open_fd(game, filename);
}
