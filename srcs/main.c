#include <../includes/main.h>

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		handler_argument(ac);
	handler_fd(av[1]);
	return (0);
}
