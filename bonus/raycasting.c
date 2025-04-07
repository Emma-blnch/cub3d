/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:50:48 by eblancha          #+#    #+#             */
/*   Updated: 2025/04/08 01:05:10 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_column(t_game *game, float *corrected_dist, int i, t_img *tex, float wall_hit, t_ray *ray)
{
	int	wall_height;
	int		wall_start;
	int		wall_end;
	int		y;
	int		tex_x;

	wall_height = (TILE_SIZE * game->win_height) / *corrected_dist;
	wall_start = (game->win_height - wall_height) / 2;
	wall_end = wall_start + wall_height;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > game->win_height)
		wall_end = game->win_height;
	y = wall_start;
	tex_x = (int)(wall_hit * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;	
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0))
		tex_x = tex->width - tex_x - 1;

	double step = (double)tex->height / wall_height;
	double tex_pos = (wall_start + (wall_height / 2 - game->win_height / 2)) * step;
	bool	is_transparent_tex = (tex == &game->tex.door_open);
	while (y < wall_end)
	{
		int tex_y = (int)tex_pos;
		tex_pos += step;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		char *pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bpp / 8));
		int color = *(unsigned int *)pixel;
		if ((color & 0x00FFFFFF) != 0 || !is_transparent_tex)
		{
			color = add_shadow(color, *corrected_dist);
			put_pixel_to_img(&game->mlx, i, y, color);
		}
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

	void	draw_ray(t_player *player, t_game *game, float angle, int col, float *perp_ray_dist)
{
	t_ray	ray;
	float	dist;
	t_img	*tex;
	double	wall_hit;

	init_ray_struct(&ray, player, angle);
	calculate_sides_distances(&ray);
	move_until_wall_is_hit(&ray, game->config.map);
	if (ray.side == 0)
		dist = (ray.side_x - ray.delta_x) * TILE_SIZE;
	else
		dist = (ray.side_y - ray.delta_y) * TILE_SIZE;
	*perp_ray_dist = dist * cos(angle - player->angle);
	if (*perp_ray_dist < 1.0f)
		*perp_ray_dist = 1.0f;
	tex = set_textures(&ray, game);
	if (ray.side == 0)
		wall_hit = ray.start_y + (dist * ray.dir_y) / TILE_SIZE; // plus clair pour exprimer le déplacement selon l'angle
	else
		wall_hit = ray.start_x + (dist * ray.dir_x) / TILE_SIZE;
	wall_hit -= floor(wall_hit);
	draw_wall_column(game, perp_ray_dist, col, tex, wall_hit, &ray);
}

void	ray_casting(t_game *game)
{
	float	start_angle;
	float	fraction;
	float	perp_ray_dist;

	
	start_angle = game->player.angle - PI / 6;
	fraction = PI / 3 / game->win_width;
	perp_ray_dist = 0;
	int i = 0;
	while (i < game->win_width)
	{
		draw_ray(&game->player, game, start_angle, i, &perp_ray_dist);
		game->z_buffer[i] = perp_ray_dist;
		start_angle += fraction;
		i++;
	}
}