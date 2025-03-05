#include "../../includes/main.h"

void	color_rgb_roof(t_game *game, t_vars *vars)
{
	int		i;
	int		j;

	(void)game;
	i = 0;
	while (i < vars->scene.win_width)
	{
		j = 0;
		while (j <vars->scene.win_height / 2)
		{
			mlx_pixel_put(vars->mlx, vars->win, i, j, 0xFFff5733);
			j++;
		}
		i++;
	}
}

