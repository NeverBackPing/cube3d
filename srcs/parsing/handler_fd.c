#include "../../includes/checkmap.h"

void	close_fd(t_game *game)
{
	if (game->fd > 0)
	{
		close(game->fd);
		game->fd = -1;
	}
}

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

void	handler_fd(char	*fd)
{
	int	i;
	int	egal;

	i = 0;
	egal = 0;
	while (fd[i] && fd[i] != '.')
		i++;
	egal = ft_strcmp((fd + i), ".cub");
	if (egal != 0)
	{
		printf("\033[0;31mError\033[0m: Bad file extension\n");
		exit(0);
	}
}
