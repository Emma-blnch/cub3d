/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:05:00 by eblancha          #+#    #+#             */
/*   Updated: 2025/04/06 13:20:14 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_menu(t_game *game)
{
	int	x;
	int	y;

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
	else
	{
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y + 40,
			0xFFFFFF, "> Exit");
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y,
			0xFF0000, "> Play");
	}
	return (0);
}

void	draw_ammo(t_game *game)
{
	int	i;
	int	spacing;
	int	x_start;
	int	y;
	int	x;

	i = 0;
	spacing = 7;
	x_start = 20;
	y = game->win_height - game->hud.ammo_h - 20;
	while (i < game->ammo)
	{
		x = x_start + i * (game->hud.ammo_w + spacing);
		mlx_put_image_to_window(game->mlx.mlx_ptr,
			game->mlx.win_ptr, game->hud.ammo_img, x, y);
		i++;
	}
}

void	draw_gun(t_game *game)
{
	int	x;
	int	y;

	x = (game->win_width - game->hud.gun_w) / 2;
	y = game->win_height - game->hud.gun_h;
	if (game->is_firing && game->fire_timer > 0)
	{
		mlx_put_image_to_window(game->mlx.mlx_ptr,
			game->mlx.win_ptr, game->hud.gun_shot, x, y);
		game->fire_timer--;
	}
	else
	{
		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
			game->hud.gun_img, x, y);
		game->is_firing = false;
	}
}
