/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:50:43 by eblancha          #+#    #+#             */
/*   Updated: 2025/04/02 13:26:53 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Étape 1 – Initialiser le rayon
void	init_ray_struct(t_ray *ray, t_player *player, float angle)
{
	ray->step_x = 0;
	ray->step_y = 0;
	ray->start_x = player->x / TILE_SIZE;
	ray->start_y = player->y / TILE_SIZE;
	ray->map_x = (int)ray->start_x;
	ray->map_y = (int)ray->start_y;
	ray->dir_x = cos(angle);
	ray->dir_y = sin(angle);
	ray->delta_x = fabs(1.0f / ray->dir_x);
	ray->delta_y = fabs(1.0f / ray->dir_y);
	ray->hit = 0;
	ray->side = -1;
}
