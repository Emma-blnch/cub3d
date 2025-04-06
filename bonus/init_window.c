/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:19:57 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/04/06 16:30:26 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			path, &tex->width, &tex->height);
	if (!tex->img)
		error_exit(game, "Error: Failed to load texture");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_length, &tex->endian);
}

static void	load_textures(t_game *game)
{
	load_texture(game, &game->tex.no, game->config.no_path);
	load_texture(game, &game->tex.so, game->config.so_path);
	load_texture(game, &game->tex.ea, game->config.ea_path);
	load_texture(game, &game->tex.we, game->config.we_path);
	for (int i = 0; i < game->sprites_count; i++)
    {
        if (game->sprites[i].path)
        {
            game->sprites[i].image.img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, 
                game->sprites[i].path, &game->sprites[i].image.width, &game->sprites[i].image.height);
            if (!game->sprites[i].image.img)
                error_exit(game, "Error: Failed to load sprite texture");
            game->sprites[i].image.addr = mlx_get_data_addr(game->sprites[i].image.img, 
                &game->sprites[i].image.bpp, &game->sprites[i].image.line_length, &game->sprites[i].image.endian);
        }
    }
}

static void	load_menu(t_game *game)
{
	game->hud.menu_bg = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./textures/menu.xpm",
			&game->hud.menu_bg_w, &game->hud.menu_bg_h);
	if (!game->hud.menu_bg)
		error_exit(game, "Error: Failed to load menu background");
}

void	load_hud(t_game *game)
{
	game->hud.gun.img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./textures/hud/gun2.xpm",
			&game->hud.gun.width, &game->hud.gun.height);
	if (!game->hud.gun.img)
		error_exit(game, "Error: Failed to load gun sprite");
	game->hud.gun.addr = mlx_get_data_addr(game->hud.gun.img,
			&game->hud.gun.bpp, &game->hud.gun.line_length,
			&game->hud.gun.endian);
	game->hud.gun_shot.img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./textures/hud/gun2-shot.xpm",
			&game->hud.gun_shot.width, &game->hud.gun_shot.height);
	if (!game->hud.gun_shot.img)
		error_exit(game, "Error: Failed to load gun shot sprite");
	game->hud.gun_shot.addr = mlx_get_data_addr(game->hud.gun_shot.img,
			&game->hud.gun_shot.bpp, &game->hud.gun_shot.line_length,
			&game->hud.gun_shot.endian);
	game->hud.ammo.img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./textures/hud/bullet32.xpm",
			&game->hud.ammo.width, &game->hud.ammo.height);
	if (!game->hud.ammo.img)
		error_exit(game, "Error: Failed to load ammo sprite");
	game->hud.ammo.addr = mlx_get_data_addr(game->hud.ammo.img,
			&game->hud.ammo.bpp, &game->hud.ammo.line_length,
			&game->hud.ammo.endian);
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
	mlx_mouse_hide(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->win_width / 2, game->win_height / 2);
	load_menu(game);
	load_hud(game);
	load_textures(game);
	mlx_hook(game->mlx.win_ptr, 17, 0, close_window, game);
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_press_linux, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, key_release_linux, game);
	mlx_mouse_hook(game->mlx.win_ptr, mouse_click, game);
	mlx_hook(game->mlx.win_ptr, 6, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx.mlx_ptr, render, game);
	mlx_loop(game->mlx.mlx_ptr);
}
