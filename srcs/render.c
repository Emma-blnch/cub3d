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
void	draw_ray(t_game *game, float ray_angle)
{
	float	new_x;
	float	new_y;
	bool	wall;
	int		i;

	new_x = game->player.pos_x;
	new_y = game->player.pos_y;
	wall = 0;
	i = 0;
	while (i < 1000 && !wall) // 1000 taille de rayon max choisie arbitrairement
	{
		new_x += cos(ray_angle) * 0.05f;
		new_y += sin(ray_angle) * 0.05f;
		if (is_wall(game, new_x, new_y))
			wall = 1;
		int screen_x = (int)(new_x * game->win_width / ft_strlen(game->config.map[0]));
		int screen_y = (int)(new_y * game->win_height / count_lines(game->config.map));
			 
		if (screen_x >= 0 && screen_x < game->win_width && 
			screen_y >= 0 && screen_y < game->win_height)
			put_pixel_to_img(&game->mlx, screen_x, screen_y, 0xFF0000);
		i++;
	}
	
}

void	ray_casting(t_game *game)
{
	float	ray_angle;
	float	fraction;
	int		i;

	i = 0;
	ray_angle = game->player.angle - PI / 6;
	fraction = PI / 3 / game->win_width;
	
	while (i < game->win_width)
	{
		draw_ray(game, ray_angle);
		ray_angle += fraction;
		i++;
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
		ray_casting(game);
		mlx_put_image_to_window(game->mlx.mlx_ptr,
			game->mlx.win_ptr, game->mlx.img, 0, 0);
	}
    return 0;
}