#include "cub3d.h"

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

void	draw_menu(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->hud.menu_bg, 0, 0);

	// à faire : adapter mise  à l'échelle
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

// ici c'est un carré
void	draw_player(t_game *game)
{
	int	player_icon_size;
	int	dx;
	int	dy;
    float scaled_x;
    float scaled_y;
    
//  position en float(précis) dans map   *  tile_width en gros 
	scaled_x = game->player.pos_x * (game->win_width / ft_strlen(game->config.map[0]));
    scaled_y = game->player.pos_y * (game->win_height / count_lines(game->config.map));
	player_icon_size = game->win_width * 0.02;
	dy = -player_icon_size;
	while (dy <= player_icon_size)
	{
		dx = -player_icon_size;
		while (dx <= player_icon_size)
		{
			put_pixel_to_img(&game->mlx, scaled_x + dx, scaled_y + dy, 0xFF0000);
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
		handle_movements(game);
		draw_background(game);
		draw_minimap(game);
		draw_player(game);
		mlx_put_image_to_window(game->mlx.mlx_ptr,
			game->mlx.win_ptr, game->mlx.img, 0, 0);
	}
    return 0;
}