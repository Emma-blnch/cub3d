/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:50:48 by eblancha          #+#    #+#             */
/*   Updated: 2025/04/06 16:06:04 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	add_shadow(int color, float corrected_dist)
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
	if((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = tex->width - tex_x - 1;

	double step = (double)tex->height / wall_height; // plus de 1.0
	double tex_pos = (wall_start + (wall_height / 2 - game->win_height / 2)) * step; // plus intuitif : on part de wall_start pour aller chercher le pixel de la colonne
	// game->win_height / 2 = milieu de l’écran
	// wall_start = haut du mur
	// wall_height / 2 = screen_center
	// wall_start - screen_center = distance entre le haut du mur et le milieu de l’écran
	// + wall_height / 2.0 = place l’origine (y=0) au milieu du mur, ça recentre ton repère
	// le tout = combien de pixels séparent le haut du mur du centre vertical du mur sur l’écran
	// * step = convertit cette distance en pixels dans la texture
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
		color = add_shadow(color, *corrected_dist);
		put_pixel_to_img(&game->mlx, i, y, color);
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

t_img	*set_textures(t_ray *ray, t_game *game)
{
	t_img	*tex;

	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			tex = &game->tex.we;
		else
			tex = &game->tex.ea;
	}
	else
	{
		if (ray->dir_y > 0)
			tex = &game->tex.no;
		else
			tex = &game->tex.so;
	}
	return (tex);
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
		wall_hit = ray.start_y + (dist * ray.dir_y)/ TILE_SIZE; // plus clair pour exprimer le déplacement selon l'angle
	else
		wall_hit = ray.start_x + (dist * ray.dir_x)/ TILE_SIZE;
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

void	calculate_sprites_dist(t_game *game)
{
	int	i;
	float	x;
	float	y;

	i = 0;
	x = 0;
	y = 0;
	while (i < game->sprites_count)
	{
		x = game->sprites[i].x - game->player.x;
		y = game->sprites[i].y - game->player.y;
		game->sprites[i].dist = sqrtf(x * x + y * y);
		i++;
	}
}

void	sort_sprites_dist(t_game *game)
{
	int	i;
	int	j;
	t_sprite tmp;

	i = 0;
	while (i < game->sprites_count - 1)
	{
		j = 0;
		while (j < game->sprites_count - i - 1)
		{
			if (game->sprites[j].dist < game->sprites[j + 1].dist)
			{
				tmp = game->sprites[j];
				game->sprites[j] = game->sprites[j + 1];
				game->sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	draw_sprites(t_game *game)
{
	calculate_sprites_dist(game);
	sort_sprites_dist(game);
	int i;
	int	sprite_x;
	int	sprite_y;
	
	float	dir_x;
	float	dir_y;
	float	perp_x;
	float	perp_y;
	float	transform_x;
	float	transform_y;
	int	sprite_screen_x;
	int	sprite_height;
	int	sprite_width;
	int	draw_start_x;
	int	draw_start_y;
	int	draw_end_x;
	int	draw_end_y;
	int	column;
	
	i = 0;
	while (i < game->sprites_count)
	{
		sprite_x = game->sprites[i].x - game->player.x;
		sprite_y = game->sprites[i].y - game->player.y;

		dir_x = cos(game->player.angle);
		dir_y = sin(game->player.angle);
		float inv_det = 1.0f / (perp_x * dir_y - dir_x * perp_y);

		perp_x = -sin(game->player.angle) * 0.66f;
		perp_y = cos(game->player.angle) * 0.66f;
		
		transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
		transform_y = inv_det * (-perp_y * sprite_x + perp_x * sprite_y);
		// transform_x = perp_x * sprite_x + perp_y * sprite_y;
		// transform_y = dir_x * sprite_x + dir_y * sprite_y; 
		if (transform_y <= 0)
		{
			i++;
			continue ;
		}
		sprite_screen_x = (int)((game->win_width / 2) * (1 + transform_x / transform_y));
		float sprite_scale = game->win_height / transform_y * TILE_SIZE;

		sprite_height = (int)sprite_scale;
		sprite_width = (int)sprite_scale;

		// sprite_height = abs((int)(game->win_height / transform_y)) * TILE_SIZE;
		draw_start_y = -sprite_height / 2 + game->win_height / 2;
        if (draw_start_y < 0)
            draw_start_y = 0;
		draw_end_y = sprite_height / 2 + game->win_height / 2;
		if (draw_end_y >= game->win_height)
			draw_end_y = game->win_height - 1;
		
		// sprite_width = abs((int)(game->win_height / transform_y)) * TILE_SIZE;
		draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= game->win_width)
			draw_end_x = game->win_width - 1;

		//loop through every vertical stripe of the sprite on screen
		column = draw_start_x;
		while (column < draw_end_x)
		{
			int tex_x = (int)(256 * (column - (-sprite_width / 2 + sprite_screen_x)) 
					* game->sprites[i].image.width / sprite_width) / 256;
			
			if (transform_y > 0 && column > 0 && column < game->win_width 
				&& transform_y < game->z_buffer[column])
			{
				int y = draw_start_y;
				while (y < draw_end_y)
				{
					int d = (y * 256) - (game->win_height * 128) + (sprite_height * 128);
					int tex_y = ((d * game->sprites[i].image.height) / sprite_height) / 256;
					u_int32_t color = *(unsigned int*)(game->sprites[i].image.addr 
							+ (tex_y * game->sprites[i].image.line_length 
							+ tex_x * (game->sprites[i].image.bpp / 8)));
					if ((color & 0x00FFFFFF) != 0)
					{
						put_pixel_to_img(&game->mlx, column, y, color);
					}
					y++;
				}
			}
			column++;
		}
		i++;
 	}
}

// pour (chaque sprite) {
//     1. calcul distance au joueur

//     1.2 trier les sprites par distance (pour éviter suraffichage)

//     2. coordonnées relatives entre joueur et sprite
//     // double spriteX = sprite[spriteOrder[i]].x - posX;
//     //  double spriteY = sprite[spriteOrder[i]].y - posY;

//     3. calcul de inverse de la matrice de caméra
//     // double invDet = 1.0 / (planeX * dirY - dirX * planeY);
//     3.2 coordonnées transformées dans espace de la caméra
//     //  double transformX = invDet * (dirY * spriteX - dirX * spriteY);
//     //  double transformY = invDet * (-planeY * spriteX + planeX * spriteY);
//     3.3 pos horizontale du sprite a ecran (colonne centrale du sprite ?)
//     //  int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

//     4. calcul hauteur du sprite projeté

//     5. calcul largeur du sprite projeté

//     6. rendu pixel par pixel comme les murs
//     // if (transformY > 0 && transformY < z_buffer[col])
//     // {
//     //     // le sprite est plus proche que le mur : on dessine
//     // }
//     // else
//     // {
//     //     // le mur est devant, on ne dessine pas ce pixel
//     // }

// }

// 2 Ko
// (ce qui est commenté sur le fichier si c'est des formules ca vient de son article, le reste c'est moi qui ai rajouté)
