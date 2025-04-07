/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:19:57 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/04/07 12:51:13 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void    load_texture(t_game *game, t_img *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path, &tex->width, &tex->height);
    if (!tex->img)
        error_exit(game, "Error: Failed to load texture");
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);   
}

static void load_textures(t_game *game)
{
    load_texture(game, &game->tex.no, game->config.no_path);
    load_texture(game, &game->tex.so, game->config.so_path);
    load_texture(game, &game->tex.ea, game->config.ea_path);
    load_texture(game, &game->tex.we, game->config.we_path);
    load_texture(game, &game->tex.door, game->config.door_path);
    
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

void    load_hud(t_game *game)
{
    game->hud.gun_img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
        "./textures/hud/gun2.xpm", &game->hud.gun_w, &game->hud.gun_h);
    if (!game->hud.gun_img)
        error_exit(game, "Error: Failed to load gun sprite");
    game->hud.menu_bg = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
        "./textures/menu.xpm", &game->hud.menu_bg_w, &game->hud.menu_bg_h);
    if (!game->hud.menu_bg)
        error_exit(game, "Error: Failed to load menu background");
}

void    init_window(t_game *game)
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
    mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_press, game);
    mlx_hook(game->mlx.win_ptr, 3, 1L << 1, key_release, game);
    load_hud(game);
    mlx_loop_hook(game->mlx.mlx_ptr, render, game);
    load_textures(game);
    mlx_loop(game->mlx.mlx_ptr);
}
