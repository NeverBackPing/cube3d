#include <../includes/main.h>

int	main(int ac, char **av)
{
	t_game	game;
	(void)game;
	(void)av;
	if (ac != 2)
		handler_argument(ac);
	handler_fd(av[1]);
	get_map(&game, av[1]);
	return (0);
}
