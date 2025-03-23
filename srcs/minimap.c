/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:27:23 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/24 00:49:33 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_tile_size(t_game *game)
{
	int	max_cols;
	int	nb_rows;
	int	width_tile;
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
	width_tile = (int)(game->win_width * 0.2 / max_cols);
	height_tile = (int)(game->win_height * 0.2 / nb_rows);
	if (height_tile < width_tile) //les deux doivent être égales, pourquoi pas if (height != widht) ? 
		width_tile = height_tile;
	if (width_tile < 1)
		width_tile = 1; // au moins un pixel 
	return (width_tile);
}

void	draw_player_minimap(t_game *game, int *tile_size)
{
	int player_x_mini;
	int player_y_mini;
	int	dx;
	int	dy;

	player_x_mini = (int)(game->player.pos_x * (*tile_size));
	player_y_mini = (int)(game->player.pos_y * (*tile_size));
	
	dy = 0;
	while (dy < *tile_size / 3)
	{
		dx = 0;
		while(dx < *tile_size / 3)
		{
			put_pixel_to_img(&game->mlx, player_x_mini + dx, player_y_mini + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}
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
            
            if (color != -1)
            {
                for (int dy = 0; dy < tile; dy++)
                {
                    for (int dx = 0; dx < tile; dx++)
                        put_pixel_to_img(&game->mlx, x * tile + dx, y * tile + dy, color);
                }
            }
			x++;
		}
		y++;
	}
	draw_player_minimap(game, &tile);
}