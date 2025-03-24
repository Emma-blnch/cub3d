/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:19:57 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/24 23:33:02 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_window(t_game *data)
{
	error_exit(data, NULL);
	return (0);
}

static int is_wall(t_game *game, int x, int y)
{
    if (y < 0 || x < 0 || !game->config.map[y] || !game->config.map[y][x] || game->config.map[y][x] == '1')
        return (1);
    return (0);
}

void	handle_movements(t_game *game)
{
    float	shift;
    float	cosinus;
    float	sinus;

    float	dx;
	float	dy;
    float	new_x;
	float	new_y;

	shift = 0.05f;
    if (game->player.left_rotate) {
        game->player.angle += 0.005f;
        if (game->player.angle >= 2 * PI)
            game->player.angle -= 2 * PI;
    }
    else if (game->player.right_rotate) {
        game->player.angle -= 0.005f;
        if (game->player.angle < 0)
            game->player.angle += 2 * PI;
    }
    cosinus = cos(game->player.angle);
    sinus = sin(game->player.angle);
    dx = 0;
    dy = 0;
    if (game->player.key_up)
	{
        dx -= cosinus * shift;
        dy -= sinus * shift;
    }
    if (game->player.key_down)
	{
        dx += cosinus * shift;
        dy += sinus * shift;
    }
    if (game->player.key_left)
	{
        dx -= sinus * shift;
        dy += cosinus * shift;
    }
    if (game->player.key_right)
	{
        dx += sinus * shift;
        dy -= cosinus * shift;
    }
    new_x = game->player.pos_x + dx;
    if (!is_wall(game, (int)new_x, (int)game->player.pos_y)) {
        game->player.pos_x = new_x;
        game->player.x = (int)new_x;
    }
    new_y = game->player.pos_y + dy;
    if (!is_wall(game, (int)game->player.pos_x, (int)new_y)) {
        game->player.pos_y = new_y;
        game->player.y = (int)new_y;
    }
}

int key_release(int key, t_game *game)
{
    printf("keycode : %d\n", key);
    if (key == XK_z)
        game->player.key_up = false;
    if (key == XK_s)
        game->player.key_down = false;
    if (key == XK_q)
        game->player.key_left = false;
    if (key == XK_d)
        game->player.key_right = false;
	if (key == XK_Left)
		game->player.left_rotate = false;
	if (key == XK_Right)
		game->player.right_rotate = false;
    return 0;
}

int key_press(int key, t_game *game)
{
    printf("keycode : %d\n", key);
	if (game->menu_active)
	{
		if (game->player.key_up)
			game->menu_selection = (game->menu_selection + 1) % 2;
		else if (game->player.key_down)
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
    if (key == XK_z)
        game->player.key_up = true;
    if (key == XK_s)
        game->player.key_down = true;
    if (key == XK_q)
        game->player.key_left = true;
    if (key == XK_d)
        game->player.key_right = true;
	if (key == XK_Left)
		game->player.left_rotate = true;
	if (key == XK_Right)
		game->player.right_rotate = true;
    if (key == XK_Escape)
        error_exit(game, NULL);
    return 0;
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
	mlx_hook(game->mlx.win_ptr, 2, 1L<<0, key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L<<1, key_release, game);
	load_hud(game);
	mlx_loop_hook(game->mlx.mlx_ptr, render, game);
	mlx_loop(game->mlx.mlx_ptr);
}
