/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:55:46 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/26 10:26:39 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int y;

	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			if (y < game->win_height / 2)
				put_pixel_to_img(&game->mlx, x, y, game->config.ceiling_color);
			else
				put_pixel_to_img(&game->mlx, x, y, game->config.floor_color);
			x++;
		}
		y++;
	}
}

void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_menu(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->hud.menu_bg, 0, 0);
	x = game->win_width / 2 - 50;
	y = game->win_height / 2 - 20;
	if (game->menu_selection == 1)
	{
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y + 40, 
			0xFF0000, "> Exit");
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y, 
			0xFFFFFF, "> Play");
	}
	else if (game->menu_selection == 0)
	{
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y + 40, 
			0xFFFFFF, "> Exit");
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y, 
			0xFF0000, "> Play");
	}
}

bool touch(float px, float py, t_game *game)
{
    int x = px / TILE_SIZE; //convertit des coordonnées en pixels (position réelle du rayon) en coordonnées sur la grille de la map
    int y = py / TILE_SIZE;

	// verif pour éviter segfault :
	if (y < 0 || x < 0 || game->config.map[y] == NULL || x >= (int)ft_strlen(game->config.map[y]))
        return true; // hors de la map = mur
    if (game->config.map[y][x] == '1')
        return true;
    return false;
}

void    draw_single_line(t_player *player, t_game *game, float start_x)
{
	//décompose l’angle de direction en deux composantes :
    float cos_angle = cos(start_x); // axe x
    float sin_angle = sin(start_x); // axe y
	
	// démarre le rayon à la position exacte du joueur, en pixels :
    float ray_x = player->x;
    float ray_y = player->y;

    while(!touch(ray_x, ray_y, game)) // tant qu'on ne touche pas un mur on continue à avancer le rayon
    {
		put_pixel_to_img(&game->mlx, ray_x, ray_y, 0xFF0000); // met un pixel rouge a position actuelle du rayon
        ray_x += cos_angle; // on avance pixel par pixel
        ray_y += sin_angle; // on avance pixel par pixel
    }
}

// rendu 3d
float distance(float x, float y) // calcule distance entre deux points dans un plan 2d
{
    return sqrt(x * x + y * y);
}

void    draw_wall(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x); // axe x
    float sin_angle = sin(start_x); // axe y
	// démarre le rayon à la position exacte du joueur, en pixels :
    float ray_x = player->x;
    float ray_y = player->y;

    while(!touch(ray_x, ray_y, game)) // tant qu'on touche pas un mur
    {
        ray_x += cos_angle; // on avance pixel par pixel
        ray_y += sin_angle;
    }

    float dist = distance(ray_x - player->x, ray_y - player->y); // calcul distance entre joueur et point où le rayon a touché un mur 
    float corrected_dist = dist * cos(start_x - player->angle); // pour éviter effet fish-eye
	// corrected_dist = dist × cos(écart entre angle du regard et angle du rayon)
	// ex: Si le rayon part de côté : cos(angle) < 1 -> on réduit la distance
	// -> projection orthogonale sur la direction du regard, comme si tous les rayons allaient tout droit
	
	// évite des divisions par zéro :
	if (corrected_dist < 0.01)
    	corrected_dist = 0.01;
    float wall_height = (TILE_SIZE * game->win_height) / corrected_dist; //plus corrected_dist est petit -> plus le mur est haut

	// centrer mur verticalement à l'écran :
    int wall_start = (game->win_height - wall_height) / 2;
    int wall_end = wall_start + wall_height;
	// haut du mur doit commencer à (milieu écran - moitié du mur)
	// et (bas = début + hauteur)

	// empecher d'écrire hors buffer :
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > game->win_height)
		wall_end = game->win_height;
    
	// on dessine un pixel de large mais d'une hauteur = wall_height
	for (int y = wall_start; y < wall_end; y++)
        put_pixel_to_img(&game->mlx, i, y, 0x0000FF);
}

int	render(t_game *game)
{
    if (!game || !game->mlx.win_ptr || !game->hud.gun_img)
		return (ft_printf("Missing render info!\n"), 1);
	if (game->menu_active)
		draw_menu(game);
	else
	{
		move_player(&game->player, game);
		ft_memset(game->mlx.addr, 0, game->win_height * game->mlx.line_length);

		draw_floor_and_ceiling(game);

		float start_x = game->player.angle - PI / 6; //(- PI / 6) pour faire vision conique
		float fraction = PI / 3 / game->win_width; // = je veux parcourir mon champ de vision de PI / 3 radians, en autant de pas qu’il y a de colonnes de pixels sur l’écran. Donc 1 rayon = 1 pixel vertical affiché = 1 angle dans le cône
		// fraction = angle total du champ de vision divisé par nombre de colonnes à l'écran
		// donc chaque rayon couvre exactement 1 pixel en largeur à l'écran

		int i = 0;
		while (i < game->win_width)
		{
			draw_wall(&game->player, game, start_x, i);
			start_x += fraction;
			i++;
		}

		draw_minimap(game);

		mlx_put_image_to_window(game->mlx.mlx_ptr,
			game->mlx.win_ptr, game->mlx.img, 0, 0);
			
		int x = (game->win_width - game->hud.gun_w) / 2;
		int y = game->win_height - game->hud.gun_h;
		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
			game->hud.gun_img, x, y);
	}
    return 0;
}


// int	render(t_game *game)
// {
//     if (!game || !game->mlx.win_ptr || !game->hud.gun_img)
// 		return (ft_printf("Missing render info!\n"), 1);
// 	if (game->menu_active)
// 		draw_menu(game);
// 	else
// 	{
// 		move_player(&game->player, game);
// 		ft_memset(game->mlx.addr, 0, game->win_height * game->mlx.line_length);

// 		draw_floor_and_ceiling(game);
// 		draw_minimap(game);
// 		// draw_square(game->player.x, game->player.y, 10, 0x00FF00, game);

// 		float start_x = game->player.angle - PI / 6; //(- PI / 6) pour faire vision conique
    	
// 		float fraction = PI / 3 / game->win_width; // = je veux parcourir mon champ de vision de PI / 3 radians, en autant de pas qu’il y a de colonnes de pixels sur l’écran. Donc 1 rayon = 1 pixel vertical affiché = 1 angle dans le cône
// 		// fraction = angle total du champ de vision divisé par nombre de colonnes à l'écran
// 		// donc chaque rayon couvre exactement 1 pixel en largeur à l'écran

// 		int i = 0;
// 		while (i < game->win_width) // FOV conique
// 		{
// 			draw_single_line(&game->player, game, start_x); // dessine rayon par rayon
// 			start_x += fraction; // va vers droite de la FOV en ayant fraction écart entre chaque rayon
// 			i++;
// 		}

// 		// draw_single_line(&game->player, game, start_x); // Un seul rayon
		
// 		mlx_put_image_to_window(game->mlx.mlx_ptr,
// 			game->mlx.win_ptr, game->mlx.img, 0, 0);
			
// 		int x = (game->win_width - game->hud.gun_w) / 2;
// 		int y = game->win_height - game->hud.gun_h;
// 		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
// 			game->hud.gun_img, x, y);
// 	}
//     return 0;
// }