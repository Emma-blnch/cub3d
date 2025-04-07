/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:50:43 by eblancha          #+#    #+#             */
/*   Updated: 2025/04/08 00:57:56 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	add_shadow(int color, float corrected_dist)
{
	double	shade;
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	shade = fmin(1.0, corrected_dist / 900.0);
	r = ((color >> 16) & 0xFF) * (1.0 - shade);
	g = ((color >> 8) & 0xFF) * (1.0 - shade);
	b = (color & 0xFF) * (1.0 - shade);
	color = (r << 16) | (g << 8) | b;
	return (color);
}