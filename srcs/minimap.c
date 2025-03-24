/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:27:23 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/24 12:02:14 by ema_blnch        ###   ########.fr       */
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

void	draw_player(t_game *game, int tile)
{
	int	size = tile / 2;
	int	px = game->player.x / TILE_SIZE * tile;
	int	py = game->player.y / TILE_SIZE * tile;
	draw_square(px - size / 2, py - size / 2, size, 0x00FF00, game);
}

void	draw_minimap(t_game *game)
{
	int		tile = get_tile_size(game);
	int		x, y;

	y = 0;
	while (game->config.map[y])
	{
		x = 0;
		while (x < (int)ft_strlen(game->config.map[y]))
		{
			char c = game->config.map[y][x];
			int color = -1;
			if (c == '1')
                color = 0x555555; // mur gris
			else if (c == '0')
                color = 0xFFFFFF; // sol blanc
			else if (ft_strchr("NSEW", c))
				color = 0xFFFFFF;
            if (color != -1)
            {
				draw_square(x * tile, y * tile, tile, color, game);
            }
			x++;
		}
		y++;
	}
	draw_player(game, tile);
}
