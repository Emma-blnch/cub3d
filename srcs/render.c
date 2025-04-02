/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:55:46 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/04/02 12:11:35 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;

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

int	render(t_game *game)
{
	if (!game || !game->mlx.win_ptr || !game->hud.gun_img)
		return (ft_printf("Missing render info!\n"), 1);
	if (game->menu_active)
	{
		draw_menu(game);
		return (0);
	}
	move_player(&game->player, game);
	ft_memset(game->mlx.addr, 0, game->win_height * game->mlx.line_length);
	draw_floor_and_ceiling(game);
	ray_casting(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr,
		game->mlx.win_ptr, game->mlx.img, 0, 0);
	// int x = (game->win_width - game->hud.gun_w) / 2;
	// int y = game->win_height - game->hud.gun_h;
	// mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
	// 	game->hud.gun_img, x, y);
	return (0);
}
