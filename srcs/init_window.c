/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:19:57 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/22 16:18:42 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_window(t_game *data)
{
	error_exit(data, NULL);
	return (0);
}

static int	handle_keypress(int key, t_game *game)
{
	if (game->menu_active)
	{
		if (key == XK_Up || key == XK_w)
			game->menu_selection = (game->menu_selection + 1) % 2;
		else if (key == XK_Down || key == XK_s)
			game->menu_selection = (game->menu_selection + 1) % 2;
		else if (key == XK_E)
		{
			if (game->menu_selection == 0)
				game->menu_active = 0; // lancer le jeu
			else
				error_exit(game, NULL); // quitter
		}
		else if (key == XK_Escape)
			error_exit(game, NULL);
	}
	else
	{
		if (key == XK_Up)
			game->player.y -= 30;
		else if (key == XK_Down)
			game->player.y += 30;
		if (key == XK_Right)
			game->player.x -= 30;
		else if (key == XK_Left)
			game->player.x += 30;
		else if (key == XK_Escape)
			error_exit(game, NULL);
	}
	return (0);
}

void	load_hud(t_game *game)
{
	game->hud.gun_img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
		"./textures/hud/weapon.xpm", &game->hud.gun_w, &game->hud.gun_h);
	if (!game->hud.gun_img)
		error_exit(game, "Error: Failed to load gun sprite");
	game->hud.menu_bg = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
		"./textures/menu.xpm", &game->hud.menu_bg_w, &game->hud.menu_bg_h);
	if (!game->hud.menu_bg)
		error_exit(game, "Error: Failed to load menu background");
	game->hud.wall = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
		"./textures/grey-stone-wall.xpm", &game->hud.wall_w, &game->hud.wall_h);
	if (!game->hud.wall)
		error_exit(game, "Error: Failed to load wall sprite");
}

void	init_window(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		error_exit(game, "Error: Failed to initiate Minilibx");
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr,
		game->win_width, game->win_height, "Cub3D");
	if (!game->mlx.win_ptr)
		error_exit(game, "Error: Failed to create window");
	game->mlx.img = mlx_new_image(game->mlx.mlx_ptr,
		game->win_width, game->win_height);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img,
		&game->mlx.bpp, &game->mlx.line_length, &game->mlx.endian);
	mlx_hook(game->mlx.win_ptr, 17, 0, close_window, game);
	mlx_key_hook(game->mlx.win_ptr, handle_keypress, game);
	load_hud(game);
	mlx_loop_hook(game->mlx.mlx_ptr, render, game);
	mlx_loop(game->mlx.mlx_ptr);
}
