/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:27:23 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/22 16:18:02 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_tile_size(t_game *game)
{
	int	max_cols;
	int	nb_rows;
	int	width_tile;
    int len;
    int height_tile;

    max_cols = 0;
	nb_rows = 0;
	while (game->config.map[nb_rows])
	{
		len = ft_strlen(game->config.map[nb_rows]);
		if (len > max_cols)
			max_cols = len;
		nb_rows++;
	}
	width_tile = (int)(game->win_width * 0.2 / max_cols);
	// mise à l'échelle pour obtenir 20% de la carte,
	// sur cette nouvelle carte miniaturisée, on divise par le
	// nombre de lignes/colonnes de la carte initiale (sa "hauteur"/sa "largeur")
	// afin d'obtenir la taille d'une ligne/colonne dans la carte mini
	// qui correspond donc à la hauteur/largeur d'une tile
	height_tile = (int)(game->win_height * 0.2 / nb_rows);
	if (height_tile < width_tile) //les deux doivent être égales, pourquoi pas if (height != widht) ? 
		width_tile = height_tile;
	if (width_tile < 1)
		width_tile = 1; // au moins un pixel 
	return (width_tile);
}

void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	// mlx->line_length  : nombre d'octets pour stocker une ligne de pixels 
	// mlx->bpp / 8 : nombre d'octets pour stocker un pixel en largeur. On multiplie par x pour avancer de x * bpp/8 pixels
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

	// adapter mise à l'échelle 
	x = game->win_width / 2 - 50;
	y = game->win_height / 2 - 20;
	
	if (game->menu_selection == 1)
	{
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y + 40, 
			0xFF0000, "> Exit");
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y, 
			0xFFFFFF, "> Play");
	}
	else
	{
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y + 40, 
			0xFFFFFF, "> Exit");
		mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y, 
			0xFF0000, "> Play");
	}
}

void	draw_player_minimap(t_game *game, int *tile_size)
{
	int player_x_mini;
	int player_y_mini;
	int	dx;
	int	dy;

	player_x_mini = game->player.x / *tile_size;
	player_y_mini = game->player.y / *tile_size;
	dy = 0;
	while (dy < *tile_size)
 	{
		dx = 0;
		while(dx < *tile_size)
		{
			put_pixel_to_img(&game->mlx, player_x_mini + dx, player_y_mini + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_game *game)
{
	int		tile = get_tile_size(game);
	int		x, y;

	y = 0;
	while (game->config.map[y])
	{
		x = 0;
		while (x < (int)ft_strlen(game->config.map[y]))
		{
			char c = game->config.map[y][x];
			int color = -1;
			if (c == '1')
                color = 0x555555; // mur gris
			else if (c == '0')
                color = 0xFFFFFF; // sol blanc
			else if (x == game->player.x && y == game->player.y)
				color = 0x00FF00; // vert pour le joueur
            if (color != -1)
            {
                for (int dy = 0; dy < tile; dy++)
                {
					// remplit chaque tuiles
                    for (int dx = 0; dx < tile; dx++)
                        put_pixel_to_img(&game->mlx, x * tile + dx, y * tile + dy, color);
                }
            }
			x++;
		}
		y++;
	}
	draw_player_minimap(game, &tile);
}

void	draw_background(t_game *game)
{
	int	x;
	int y;

	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			put_pixel_to_img(&game->mlx, x, y, 0x0080FF);
			x++;
		}
		y++;
	}
}

// ici c'est un carré
void	draw_player(t_game *game)
{
	int	player_icon_size;
	int	dx;
	int	dy;

	player_icon_size = game->win_width * 0.02;
	dy = -player_icon_size;
	while (dy <= player_icon_size)
	{
		dx = -player_icon_size;

		while (dx <= player_icon_size)
		{
			put_pixel_to_img(&game->mlx, game->player.x + dx, game->player.y + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}	
}

int	render(t_game *game)
{
    if (!game || !game->mlx.win_ptr || !game->hud.gun_img)
		return (ft_printf("Missing render info!\n"), 1);
	if (game->menu_active)
		draw_menu(game);
	else
	{
		draw_background(game);
		draw_minimap(game);
		draw_player(game);
		mlx_put_image_to_window(game->mlx.mlx_ptr,
			game->mlx.win_ptr, game->mlx.img, 0, 0);
	}
    return 0;
}