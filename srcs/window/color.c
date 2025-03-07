#include "window.h"
#include "../../includes/main.h"
#include <stdlib.h>

void	ft_draw_background(t_game *game, char *data, int size_line)
{
	int	x;
	int	y;
	int	*img_data = (int *)data;

	y = 0;
	while (y < SCREENY)
	{
		x = 0;
		while (x < SCREENX)
		{
			if (y < SCREENY / 2)
				img_data[y * (size_line / 4) + x] = game->texture.roof_color;
			else
				img_data[y * (size_line / 4) + x] = game->texture.ground_color;
			x++;
		}
		y++;
	}
}

