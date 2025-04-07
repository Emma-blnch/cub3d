#include "cub3d.h"

t_img	*set_textures(t_ray *ray, t_game *game)
{
	t_img	*tex;
	char	c;

	c = game->config.map[ray->map_y][ray->map_x];
	if (c == '3')
		return (&game->tex.door);
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			tex = &game->tex.ea;
		else
			tex = &game->tex.we;
	}
	else
	{
		if (ray->dir_y > 0)
			tex = &game->tex.so;
		else
			tex = &game->tex.no;
	}
	return (tex);
}

static void    load_texture(t_game *game, t_img *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path, &tex->width, &tex->height);
    if (!tex->img)
        error_exit(game, "Error: Failed to load texture");
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);   
}

static void load_sprites(t_game *game)
{
    int i;

    i = 0;
    while (i < game->sprites_count)
    {
        if (game->sprites[i].path)
        {
            game->sprites[i].image.img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, 
                game->sprites[i].path, &game->sprites[i].image.width, &game->sprites[i].image.height);
            if (!game->sprites[i].image.img)
                error_exit(game, "Error: Failed to load sprite texture");
            game->sprites[i].image.addr = mlx_get_data_addr(game->sprites[i].image.img, 
                &game->sprites[i].image.bpp, &game->sprites[i].image.line_length, &game->sprites[i].image.endian);
        }
        i++;
    }
}

void load_textures(t_game *game)
{
    load_texture(game, &game->tex.no, game->config.no_path);
    load_texture(game, &game->tex.so, game->config.so_path);
    load_texture(game, &game->tex.ea, game->config.ea_path);
    load_texture(game, &game->tex.we, game->config.we_path);
    load_texture(game, &game->tex.door, game->config.door_path);
    load_sprites(game);
}

void    load_hud(t_game *game)
{
    game->hud.gun_img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
        "./textures/hud/gun2.xpm", &game->hud.gun_w, &game->hud.gun_h);
    if (!game->hud.gun_img)
        error_exit(game, "Error: Failed to load gun sprite");
    game->hud.menu_bg = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
        "./textures/menu.xpm", &game->hud.menu_bg_w, &game->hud.menu_bg_h);
    if (!game->hud.menu_bg)
        error_exit(game, "Error: Failed to load menu background");
}