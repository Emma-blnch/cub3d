/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:50:48 by eblancha          #+#    #+#             */
/*   Updated: 2025/04/02 08:50:48 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_column(t_game *game, float *corrected_dist, int i)
{
    float	wall_height;
    int		wall_start;
    int		wall_end;
	int		y;

	wall_height = (TILE_SIZE * game->win_height) / *corrected_dist;
	wall_start = (game->win_height - wall_height) / 2;
	wall_end = wall_start + wall_height;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > game->win_height)
		wall_end = game->win_height;
	y = wall_start;
	while (y < wall_end)
	{
        put_pixel_to_img(&game->mlx, i, y, 0x0000FF);
		y++;
	}
}

static void	calculate_sides_distances(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (ray->start_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0f - ray->start_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (ray->start_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0f - ray->start_y) * ray->delta_y;
	}
}

void	move_until_wall_is_hit(t_ray *ray, char **map)
{
	while (!ray->hit)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(ray->map_x * TILE_SIZE, ray->map_y * TILE_SIZE, map))
			ray->hit = 1;
	}
}

static void	draw_ray(t_player *player, t_game *game, float angle, int col)
{
	t_ray	ray;
	float	dist;
	float	corrected;

	init_ray_struct(&ray, player, angle);
	calculate_sides_distances(&ray);
	move_until_wall_is_hit(&ray, game->config.map);
	if (ray.side == 0)
		dist = (ray.side_x - ray.delta_x) * TILE_SIZE;
	else
		dist = (ray.side_y - ray.delta_y) * TILE_SIZE;
	corrected = dist * cos(angle - player->angle);
	if (corrected < 0.01)
		corrected = 0.01;
	draw_wall_column(game, &corrected, col);
}

void	ray_casting(t_game *game)
{
	float	start_angle;
	float	fraction;

	start_angle = game->player.angle - PI / 6;
	fraction = PI / 3 / game->win_width;
	int i = 0;
	while (i < game->win_width)
	{
		draw_ray(&game->player, game, start_angle, i);
		start_angle += fraction;
		i++;
	}
}