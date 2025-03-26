#include "cub3d.h"


static void	draw_wall_column(t_game *game, float *corrected_dist, int i)
{
    float	wall_height;
    int		wall_start;
    int		wall_end;
	int		y;

	wall_height = (TILE_SIZE * game->win_height) / *corrected_dist;
	wall_start = (game->win_height - wall_height) / 2;
	wall_end = wall_start + wall_height;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > game->win_height)
		wall_end = game->win_height;
	y = wall_start;
	while (y < wall_end)
	{
        put_pixel_to_img(&game->mlx, i, y, 0x0000FF);
		y++;
	}
}

static void    draw_ray(t_player *player, t_game *game, float start_x, int i)
{
    float	ray_x;
    float	ray_y;
	float	dist;
    float	corrected_dist;

	ray_x = player->x;
	ray_y = player->y;
    while(!is_wall(ray_x, ray_y, game->config.map))
    {
        ray_x += cos(start_x); // pourquoi pas de facteur ici ?? 
        ray_y += sin(start_x);
    }
    dist = sqrtf((ray_x - player->x) * (ray_x - player->x) + (ray_y - player->y) * (ray_y - player->y));
	corrected_dist = dist * cos(start_x - player->angle);
	if (corrected_dist < 0.01)
		corrected_dist = 0.01;
	draw_wall_column(game, &corrected_dist, i);
}

void	ray_casting(t_game *game)
{
	float start_x;
	float fraction;

	start_x = game->player.angle - PI / 6;
	fraction = PI / 3 / game->win_width;
	int i = 0;
	while (i < game->win_width)
	{
		draw_ray(&game->player, game, start_x, i);
		start_x += fraction;
		i++;
	}
}