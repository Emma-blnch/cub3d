/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:19:57 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/24 15:38:49 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_window(t_game *data)
{
	error_exit(data, NULL);
	return (0);
}

void	handle_movements(t_game *game)
{
	float	shift; // de combien de pixels on se déplace, ici utile pour se déplacer dans un pixel
	int		new_y; // avec ça on peut se déplacer de player.y à "player.y,999" par ex, ce qui était pas possible avant
	// car un mur à 1 pixel de notre position nous bloquait. 
	int		new_x;
	float		cosinus;
	float		sinus;

	cosinus = cos(game->player.angle);
	sinus = sin(game->player.angle);
	shift = 0.05f;
	if (game->player.key_up)
	{
		game->player.pos_x -= shift * cosinus;
		game->player.pos_y -= shift * sinus;
		new_x = (int)game->player.pos_x;
		new_y = (int)game->player.pos_y;
		if (new_y != game->player.y || new_x != game->player.x) // si ça change les coordonnées entières, donc si on a changé de tile
		{
			//on check si les coordonnées entières sont les coordonnées d'un mur
			if (new_y >= 0 && game->config.map[new_y][game->player.x] != '1')
			{
				game->player.y = new_y;
				game->player.x = new_x;
			}
			else
			{
				printf("you hit a wall\n");
				game->player.pos_y += shift * sinus; // s'il y a un mur on bouge pas
				game->player.pos_x += shift * cosinus;
			}
		}
	}
	else if (game->player.key_down)
	{
		game->player.pos_y += shift * sinus;
		game->player.pos_x += shift * cosinus;
		new_y = (int)game->player.pos_y;
		new_x = (int)game->player.pos_x;

		if (new_y != game->player.pos_y || new_x != game->player.pos_x)
		{
			if (game->config.map[new_y] && game->config.map[new_y][game->player.x] != '1')
			{
				game->player.y = new_y;
				game->player.x = new_x;
			}
			else
			{
				printf("you hit a wall\n");
				game->player.pos_y -= shift * sinus;
				game->player.pos_x -= shift * cosinus;
			}
		}
	}
	else if (game->player.key_left)
	{
		game->player.pos_x += shift;
		new_x = (int)game->player.pos_x;
		if (new_x != game->player.pos_x)
		{
			if (new_x >= 0 && game->config.map[game->player.y][new_x] != '1')
				game->player.x = new_x;
			else
			{
				printf("you hit a wall\n");
				game->player.pos_x -= shift;
			}
		}
	}
	else if (game->player.key_right)
	{
		game->player.pos_x -= shift;
		new_x = (int)game->player.pos_x;
		if (new_x != game->player.pos_x)
		{
			if (game->config.map[game->player.y] && game->config.map[game->player.y][new_x] != '1')
				game->player.x = new_x;
			else
			{
				game->player.pos_x += shift;
				printf("you hit a wall\n");
			}
		}
	}
}

int key_release(int key, t_game *game)
{
    printf("keycode : %d\n", key);
    if (key == XK_Up || key == XK_w)
        game->player.key_up = false;
    if (key == XK_Down || key == XK_s)
        game->player.key_down = false;
    if (key == XK_Right)
        game->player.key_right = false;
    if (key == XK_Left)
        game->player.key_left = false;
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
    if (key == XK_Up || key == XK_w)
        game->player.key_up = true;
    if (key == XK_Down || key == XK_s)
        game->player.key_down = true;
    if (key == XK_Right)
        game->player.key_right = true;
    if (key == XK_Left)
        game->player.key_left = true;
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
