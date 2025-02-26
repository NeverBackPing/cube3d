#include "checkmap.h"

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