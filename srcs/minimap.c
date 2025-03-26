/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:27:23 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/26 17:39:09 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tile_size(t_game *game)
{
	int	max_cols;
	int	nb_rows;
	int	tile;
    int len;
    int height_tile;

    max_cols = 0;
	nb_rows = 0;
	while (game->config.map[nb_rows])
	{
		len = ft_strlen(game->config.map[nb_rows]);
		if (len > max_cols)
			max_cols = len;
		nb_rows++;
	}
	tile = (int)(game->win_width * 0.2 / max_cols);
	height_tile = (int)(game->win_height * 0.2 / nb_rows);
	if (height_tile < tile)
		tile = height_tile;
	if (tile < 1)
		tile = 1;
	return (tile);
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int dy = 0; dy < size; dy++)
	{
		for (int dx = 0; dx < size; dx++)
		{
			put_pixel_to_img(&game->mlx, x + dx, y + dy, color);
		}
	}
}

void	draw_player_minimap(t_game *game, int tile)
{
	int	size = tile / 2;
	int	px = game->player.x / TILE_SIZE * tile;
	int	py = game->player.y / TILE_SIZE * tile;
	draw_square(px - size / 2, py - size / 2, size, 0x00FF00, game);
}

void	draw_ray_on_minimap(t_game *game, float angle)
{
	float	ray_x;
	float	ray_y;
	float	cos_a;
	float	sin_a;
	int		tile_size;

	ray_x = game->player.x;
	ray_y = game->player.y;
	cos_a = cos(angle);
	sin_a = sin(angle);
	tile_size = get_tile_size(game);
	while (!is_wall(ray_x, ray_y, game->config.map))
	{
		int mini_x = (ray_x / TILE_SIZE) * tile_size;
		int mini_y = (ray_y / TILE_SIZE) * tile_size;
		put_pixel_to_img(&game->mlx, mini_x, mini_y, 0xFF0000);
		ray_x += cos_a;
		ray_y += sin_a;
	}
}

void	ray_casting_minimap(t_game *game)
{
	float	start_x;
	float	fraction;
	int		i;

	i = 0;
	fraction = PI / 3 / game->win_width;
	start_x = game->player.angle - PI / 6;
		while (i < game->win_width)
		{
			draw_ray_on_minimap(game, start_x);
			start_x += fraction;
			i++;
		}
}

int	set_color(char **map, int y, int x)
{
	int		color;

	color = -1;
	if (map[y][x] == '1')
		color = 0x555555;
	else if (map[y][x] == '0')
		color = 0xFFFFFF;
	else if (ft_strchr("NSEW", map[y][x]))
		color = 0xFFFFFF;
	return (color);
}

void	draw_minimap(t_game *game)
{
	int		tile = get_tile_size(game);
	int		y;
	int		x;
	int		color;

	tile = get_tile_size(game);
	y = 0;
	while (game->config.map[y])
	{
		x = 0;
		while (x < (int)ft_strlen(game->config.map[y]))
		{
			color = set_color(game->config.map, y, x);
            if (color != -1)
				draw_square(x * tile, y * tile, tile, color, game);
			x++;
		}
		y++;
	}
	draw_player_minimap(game, tile);
	ray_casting_minimap(game);
}
