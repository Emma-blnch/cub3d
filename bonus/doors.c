#include "cub3d.h"

static void	open_and_close_vertical_doors(t_game *game)
{
	int	player_x;
	int	player_y;
	
	player_x = game->player.x / TILE_SIZE;
	player_y = game->player.y / TILE_SIZE;
	if (game->player.angle >= PI / 2 && game->player.angle <= 3 * PI / 2)
	{
		if (game->config.map[player_y][player_x - 1] == '3')
			game->config.map[player_y][player_x - 1] = '4';
		else if (game->config.map[player_y][player_x - 1] == '4')
			game->config.map[player_y][player_x - 1] = '3';
	}
	if ((game->player.angle >= 0 && game->player.angle < PI / 2) 
		|| (game->player.angle > 3 * PI / 2 && game->player.angle <= 2 * PI))
	{
		if (game->config.map[player_y][player_x + 1] == '3')
			game->config.map[player_y][player_x + 1] = '4';
		else if (game->config.map[player_y][player_x + 1] == '4')
			game->config.map[player_y][player_x + 1] = '3';
	}
}

static void	open_and_close_horizontal_doors(t_game *game)
{
	int	player_x;
	int	player_y;
	
	player_x = game->player.x / TILE_SIZE;
	player_y = game->player.y / TILE_SIZE;
	if (game->player.angle >= PI && game->player.angle <= 2 * PI)
	{
		if (game->config.map[player_y - 1][player_x] == '3')
			game->config.map[player_y - 1][player_x] = '4';
		else if (game->config.map[player_y - 1][player_x] == '4')
			game->config.map[player_y - 1][player_x] = '3';
	}
	if (game->player.angle >= 0 && game->player.angle <= PI)
	{
		if (game->config.map[player_y + 1][player_x] == '3')
			game->config.map[player_y + 1][player_x] = '4';
		else if (game->config.map[player_y + 1][player_x] == '4')
			game->config.map[player_y + 1][player_x] = '3';
	}
}

void open_and_close_doors(t_game *game)
{
	open_and_close_horizontal_doors(game); // https://english.stackexchange.com/questions/60372/is-there-a-word-that-means-both-opening-and-closing-a-door
	open_and_close_vertical_doors(game);
}