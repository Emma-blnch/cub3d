/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:20:31 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/11 14:05:31 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_matrix *data)
{
	error_exit(data, NULL);
	return (0);
}

int	handle_key(int keycode, t_matrix *data)
{
	if (keycode == ESC_KEY)
		error_exit(data, NULL);
	else if (keycode == UP_KEY)
		data->offset_y -= 10;
	else if (keycode == DOWN_KEY)
		data->offset_y += 10;
	else if (keycode == LEFT_KEY)
		data->offset_x -= 10;
	else if (keycode == RIGHT_KEY)
		data->offset_x += 10;
	else if (keycode == RESET_KEY)
		reset(data);
	else if (keycode == 105)
	{
		data->is_isometric = !data->is_isometric;
		center_map(data);
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	clear_image(data->image);
	render_grid(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->image->img, 0, 0);
	put_msg(data);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_matrix *data)
{
	(void)x;
	(void)y;
	if (button == 4)
		data->zoom += 1;
	else if (button == 5)
		data->zoom -= 1;
	if (data->zoom < 1)
		data->zoom = 1;
	center_map(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	clear_image(data->image);
	render_grid(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->image->img, 0, 0);
	put_msg(data);
	return (0);
}
