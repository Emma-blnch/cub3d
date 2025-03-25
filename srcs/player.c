#include "cub3d.h"

void    init_player(t_player *player, t_game *game)
{
    player->x = (game->config.player_x + 0.5) * TILE_SIZE;
    player->y = (game->config.player_y + 0.5) * TILE_SIZE;
	if (game->config.player_dir == 'N')
		player->angle = PI / 2;
	else if (game->config.player_dir == 'S')
		player->angle = 3 * PI / 2;
	else if (game->config.player_dir == 'E')
		player->angle = 0;
	else if (game->config.player_dir == 'W')
		player->angle = PI;
    player->key_down = false;
    player->key_left = false;
    player->key_rigth = false;
    player->key_up = false;
    player->left_rotate = false;
    player->right_rotate = false;
}

static int	is_wall(float x, float y, char **map)
{
	int	map_x;
	int	map_y;

    map_x = (int)(x / TILE_SIZE);
    map_y = (int)(y / TILE_SIZE);
	if (map[map_y] == NULL || map[map_y][map_x] == '\0')
		return (1); // hors de la map = mur
	if (map[map_y][map_x] == '1')
		return (1); // mur
	return (0); // pas de mur
}

void    move_player(t_player *player, t_game *game)
{
    int speed = 3;
    float new_x = player->x;
	float new_y = player->y;
    float cos_angle = cos(player->angle); // décalage sur axe x
    float sin_angle = sin(player->angle); // décalage sur axe y
    float angle_speed = 0.03; // vitesse de rotation (pas mettre trop rapide sinon effet bizarre)

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    // pour éviter angles négatifs ou qui dépassent 360° :
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->key_up) // avancer
    {
        new_x += cos_angle * speed;
        new_y += sin_angle * speed;
    }
    if (player->key_down) // reculer
    {
        new_x -= cos_angle * speed;
        new_y -= sin_angle * speed;
    }
    if (player->key_left) // gauche
    {
        new_y -= cos_angle * speed;
        new_x += sin_angle * speed;
    }
    if (player->key_rigth) // droite
    {
        new_y += cos_angle * speed;
        new_x -= sin_angle * speed;
    }
    if (!is_wall(new_x, player->y, game->config.map))
		player->x = new_x;
	if (!is_wall(player->x, new_y, game->config.map))
		player->y = new_y;
}

// float angle_speed = 0.03; // vitesse de rotation (pas mettre trop rapide sinon effet bizarre)

// if (player->left_rotate)
// player->angle -= angle_speed;
// if (player->right_rotate)
// player->angle += angle_speed;
// // pour éviter angles négatifs ou qui dépassent 360° :
// if (player->angle > 2 * PI)
// player->angle = 0;
// if (player->angle < 0)
// player->angle = 2 * PI;