/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:20:31 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/26 18:00:03 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_game *data)
{
	error_exit(data, NULL);
	return (0);
}

static int	handle_menu(int keycode, t_game *game)
{
	if (keycode == Up || keycode == W)
		game->menu_selection = (game->menu_selection + 1) % 2;
	else if (keycode == Down || keycode == S)
		game->menu_selection = (game->menu_selection + 1) % 2;
	else if (keycode == E)
	{
		if (game->menu_selection == 0)
			game->menu_active = 0;
		else
			error_exit(game, NULL);
	}
	else if (keycode == Escape)
		error_exit(game, NULL);
	return (0);
}

int key_press(int keycode, t_game *game)
{
	if (game->menu_active)
		handle_menu(keycode, game);
    if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
        game->player.key_down = true;
	if (keycode == D)
        game->player.key_rigth = true;
	if (keycode == A)
        game->player.key_left = true;
	if (keycode == LEFT)
        game->player.left_rotate = true;
	if (keycode == RIGHT)
        game->player.right_rotate = true;
	if (keycode == Escape)
		error_exit(game, NULL);
	return (0);
}

int key_release(int keycode, t_game *game)
{
	t_player *player;
	
	player = &game->player;
	if (game->menu_active)
		return (0);
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == D)
		player->key_rigth = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}
