typedef struct s_sprite
{
    double x;
    double y;
    t_img texture;
    double dist;
} t_sprite;

calculer un z_buffer (distance au mur) pour éviter affichage sprite derriere mur ?
// dans fonction raycasting :
// double z_buffer[game->win_width];
// while (i < game->win_width)
// {
// 	draw_ray(...);
// 	z_buffer[i] = corrected;
// }

pour (chaque sprite) {
    1. calcul distance au joueur

    1.2 trier les sprites par distance (pour éviter suraffichage)

    2. coordonnées relatives entre joueur et sprite
    // double spriteX = sprite[spriteOrder[i]].x - posX;
    //  double spriteY = sprite[spriteOrder[i]].y - posY;

    3. calcul de inverse de la matrice de caméra
    // double invDet = 1.0 / (planeX * dirY - dirX * planeY);
    3.2 coordonnées transformées dans espace de la caméra
    //  double transformX = invDet * (dirY * spriteX - dirX * spriteY);
    //  double transformY = invDet * (-planeY * spriteX + planeX * spriteY);
    3.3 pos horizontale du sprite a ecran (colonne centrale du sprite ?)
    //  int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

    4. calcul hauteur du sprite projeté

    5. calcul largeur du sprite projeté

    6. rendu pixel par pixel comme les murs
    // if (transformY > 0 && transformY < z_buffer[col])
    // {
    //     // le sprite est plus proche que le mur : on dessine
    // }
    // else
    // {
    //     // le mur est devant, on ne dessine pas ce pixel
    // }

}


a modif :
move_player : if (is_wall(new_x, player->y, game->config.map) || is_sprite(new_x, player->y, game->config.map))
pour éviter collisions

dupliquer is_wall en is_sprite :
bool is_sprite(float px, float py, char **map)
{
    int x = px / TILE_SIZE;
    int y = py / TILE_SIZE;

    if (y < 0 || x < 0 || map[y] == NULL || x >= (int)ft_strlen(map[y]))
        return (false);
    return (map[y][x] == '2');
}

remettre is_wall comme était (rayons peuvent passer a travers sprite car sprite peut etre cahche par mur et affichage gerer apres)

implemebter draw_sprite de lodev :











void	sort_sprites(t_sprite *sprites, int count)
{
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (sprites[i].dist < sprites[j].dist)
			{
				t_sprite tmp = sprites[i];
				sprites[i] = sprites[j];
				sprites[j] = tmp;
			}
		}
	}
}

static void calculate_distance(t_game *game)
{
    for (int i = 0; i < game->num_sprites; i++)
    {
        t_sprite *spr = &game->sprites[i];
        double dx = spr->x - game->player.x;
        double dy = spr->y - game->player.y;
        spr->dist = dx * dx + dy * dy;
    }
}

void draw_sprites(game)
{
    calculate_distance(game);
    sort_sprites(game->sprites, game->num_sprites);
    for (int i = 0; i < game->num_sprites; i++)
    {
        double dx = spr->x - game->player.x;
		double dy = spr->y - game->player.y;
        double inv_det = 1.0 / (game->plane_x * game->player.dir_y - game->player.dir_x * game->plane_y);
        double transform_x = inv_det * (game->player.dir_y * dx - game->player.dir_x * dy);
        double transform_y = inv_det * (-game->plane_y * dx + game->plane_x * dy);
        int sprite_screen_x = (int)((game->win_width / 2) * (1 + transform_x / transform_y));
    }
}