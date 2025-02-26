#include "checkmap.h"

void	handler_argument(int ac)
{
	if (ac < 2)
		printf("\033[0;31mError\033[0m: Please make in input <./cube3d filename.cub>\n");
	else
		printf("\033[0;31mError\033[0m: Sorry to many argument !\n");
	exit(0);
}