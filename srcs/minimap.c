/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:27:23 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/21 19:02:37 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_tile_size(t_game *game)
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

void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
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
				color = 0x00FF00; // vert pour le joueur
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
}

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

void	draw_menu(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->hud.menu_bg, 0, 0);
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

int	render(t_game *game)
{
    if (!game || !game->mlx.win_ptr || !game->hud.gun_img)
		return (ft_printf("Missing render info!\n"), 1);
	if (game->menu_active)
		draw_menu(game);
	else
	{
		draw_floor_and_ceiling(game);
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

