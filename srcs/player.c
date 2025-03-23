#include "cub3d.h"

// si trouve un player, elle l'initialise et boucle pour vérifier que c'est le seul
void	store_player(t_game *data)
{
	int	y;
	int	x;
	char	**map;
    
    map = data->config.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				if (data->player.dir)
					error_exit(data, "Error: Multiple player positions found");
				data->player.x = x;
				data->player.y = y;
				data->player.pos_x = (float)x + 0.5f; //centre sur la position
				data->player.pos_y = (float)y + 0.5f;
				data->player.dir = map[y][x];
				data->player.angle = PI / 2;
				map[y][x] = '0';
				return;
			}
			x++;
		}
		y++;
	}
	error_exit(data, "Error: No player position found");
}