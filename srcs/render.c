/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:55:46 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/26 18:59:25 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int y;

	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			if (y < game->win_height / 2)
				put_pixel_to_img(&game->mlx, x, y, game->config.ceiling_color);
			else
				put_pixel_to_img(&game->mlx, x, y, game->config.floor_color);
			x++;
		}
		y++;
	}
}

void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_menu(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->hud.menu_bg, 0, 0);
		// adapter  ?
	x = game->win_width / 2 - 50;
	y = game->win_height / 2 - 20;
	if (game->menu_selection == 1)
	{
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y + 40, 
			0xFF0000, "> Exit");
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y, 
			0xFFFFFF, "> Play");
	}
	else if (game->menu_selection == 0)
	{
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y + 40, 
			0xFFFFFF, "> Exit");
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y, 
			0xFF0000, "> Play");
	}
}

bool is_wall(float px, float py, char **map)
{
    int x = px / TILE_SIZE;
    int y = py / TILE_SIZE;

	if (y < 0 || x < 0 || map[y] == NULL || x >= (int)ft_strlen(map[y]))
        return (true);
    if (map[y][x] == '1')
        return (true);
    return (false);
}

float	distance(float x, float y)
{
    return (sqrt(x * x + y * y));
}

void	draw_wall_column(t_game *game, float *corrected_dist, int i)
{

    float wall_height = (TILE_SIZE * game->win_height) / *corrected_dist;

    int wall_start = (game->win_height - wall_height) / 2;
    int wall_end = wall_start + wall_height;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > game->win_height)
		wall_end = game->win_height;
	for (int y = wall_start; y < wall_end; y++)
        put_pixel_to_img(&game->mlx, i, y, 0x0000FF);
}

void    draw_ray(t_player *player, t_game *game, float start_x, int i)
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
	dist = distance(ray_x - player->x, ray_y - player->y);
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

int	render(t_game *game)
{
    if (!game || !game->mlx.win_ptr || !game->hud.gun_img)
		return (ft_printf("Missing render info!\n"), 1);
	if (game->menu_active)
		draw_menu(game);
	else
	{
		move_player(&game->player, game);
		ft_memset(game->mlx.addr, 0, game->win_height * game->mlx.line_length);
		draw_floor_and_ceiling(game);
		ray_casting(game);
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx.mlx_ptr,
			game->mlx.win_ptr, game->mlx.img, 0, 0);
		int x = (game->win_width - game->hud.gun_w) / 2;
		int y = game->win_height - game->hud.gun_h;
		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
			game->hud.gun_img, x, y);
	}
    return 0;
}