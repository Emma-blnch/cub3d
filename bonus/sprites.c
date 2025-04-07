#include "cub3d.h"

static void calculate_sprites_dist(t_game *game)
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

static void sort_sprites_dist(t_game *game)
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

		perp_x = -sin(game->player.angle) * 0.66f;
		perp_y = cos(game->player.angle) * 0.66f;

		float inv_det = 1.0f / (perp_x * dir_y - dir_x * perp_y);
		
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
