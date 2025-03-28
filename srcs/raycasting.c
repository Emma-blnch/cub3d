#include "cub3d.h"


static void	draw_wall_column(t_game *game, float *corrected_dist, int i)
{
    float	wall_height;
    int		wall_start;
    int		wall_end;
	int		y;

	wall_height = (TILE_SIZE * game->win_height) / *corrected_dist;
	wall_start = (game->win_height - wall_height) / 2;
	wall_end = wall_start + wall_height;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > game->win_height)
		wall_end = game->win_height;
	y = wall_start;
	while (y < wall_end)
	{
        put_pixel_to_img(&game->mlx, i, y, 0x0000FF);
		y++;
	}
}

// static void    draw_ray(t_player *player, t_game *game, float start_x, int i)
// {
//     float	ray_x;
//     float	ray_y;
// 	float	dist;
//     float	corrected_dist;

// 	ray_x = player->x;
// 	ray_y = player->y;
//     while(!is_wall(ray_x, ray_y, game->config.map))
//     {
//         ray_x += cos(start_x); // pourquoi pas de facteur ici ?? 
//         ray_y += sin(start_x);
//     }
//     dist = sqrtf((ray_x - player->x) * (ray_x - player->x) + (ray_y - player->y) * (ray_y - player->y));
// 	corrected_dist = dist * cos(start_x - player->angle);
// 	if (corrected_dist < 0.01)
// 		corrected_dist = 0.01;
// 	draw_wall_column(game, &corrected_dist, i);
// }


static void	draw_ray(t_player *player, t_game *game, float angle, int col)
{
	// Position du joueur, convertie en cases (car DDA travaille en cases)
	float start_x = player->x / TILE_SIZE;
	float start_y = player->y / TILE_SIZE;

	// Position de la case actuelle dans la map
	int map_x = (int)start_x;
	int map_y = (int)start_y;

	// Direction du rayon (à partir de l'angle)
	float ray_dir_x = cos(angle);
	float ray_dir_y = sin(angle);

	// Distance entre chaque step dans chaque direction
	float delta_dist_x = fabs(1.0f / ray_dir_x); // retourne valeur absolue en float
	float delta_dist_y = fabs(1.0f / ray_dir_y); // détails plus bas

	int step_x, step_y; // direction dans laquelle va avancer le rayon en x ou y
	float side_dist_x, side_dist_y; // distance en pixels entre position actuelle du joueur et premier bord de case qu’on va toucher
	int side; // 0 = mur vertical (rayon a avancé en X), 1 = mur horizontal (rayon a avancé en Y)
	
	// Étape directionnelle X
	if (ray_dir_x < 0)
	{
		step_x = -1; // on va a gauche
		side_dist_x = (start_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1; // on va a droite
		side_dist_x = (map_x + 1.0f - start_x) * delta_dist_x;
	}
	// Étape directionnelle Y
	if (ray_dir_y < 0)
	{
		step_y = -1; // on va en haut
		side_dist_y = (start_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1; // on va en bas
		side_dist_y = (map_y + 1.0f - start_y) * delta_dist_y;
	}

	// DDA loop : avancer case par case jusqu'a toucher un mur
	int hit = 0;
	while (!hit)
	{
		// Avance dans la direction où la distance est la plus petite
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0; // a frappé un mur sur l’axe X (mur vertical)
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; // a frappé un mur sur l’axe Y (mur horizontal)
		}
		if (is_wall(map_x * TILE_SIZE, map_y * TILE_SIZE, game->config.map))
			hit = 1;
	}

	// Calcule la distance entre le joueur et le point d'impact (en cases)
	float dist;
	if (side == 0)
		dist = (side_dist_x - delta_dist_x);
	else
		dist = (side_dist_y - delta_dist_y);

	// convertit la distance en cases vers pixels pour affichage (TILE_SIZE = taille réelle)
	dist *= TILE_SIZE;

	// correction fish-eye
	float corrected = dist * cos(angle - player->angle);
	if (corrected < 0.01)
		corrected = 0.01;
	draw_wall_column(game, &corrected, col);
}

// Pourquoi cette formule "float delta_dist_x = fabs(1.0f / ray_dir_x); " ? (ce sera la meme pour y)
// à la base le calcul est : deltaDistX = sqrt(1 + (rayDirY / rayDirX) * (rayDirY / rayDirX));
// on peut simplifier le calcul en : deltaDistX = sqrt(1 + (rayDirY / rayDirX)²);

// L’idée derrière deltaDistX et deltaDistY, c’est de savoir combien de distance réelle (dans le monde en pixels) il faut parcourir pour traverser une case
// 
// Si tu as un vecteur direction ray_dir_x / ray_dir_y, alors la longueur du vecteur pour atteindre une case entière dépend de son inclinaison.
// Tu peux modéliser un triangle rectangle dont :
// 	- l'hypoténuse = la distance à la case suivante
// 	- un des côtés = 1 (car on traverse une case)
// 	- l'autre côté = tangent de l'angle

// mais notre vecteur direction est unitaire (défini avec cos(angle) et sin(angle)) donc :
// ray_dir_x² + ray_dir_y² = 1
// → ray_dir_y² = 1 - ray_dir_x²

// donc :
// deltaDistX = sqrt(1 + (ray_dir_y² / ray_dir_x²))
//            = sqrt(1 + (1 - ray_dir_x²) / ray_dir_x²)
//            = sqrt((ray_dir_x² + 1 - ray_dir_x²) / ray_dir_x²)
//            = sqrt(1 / ray_dir_x²)
//            = 1 / |ray_dir_x|
//            = fabs(1.0 / ray_dir_x)

// c'est plus rapide a calculer que avec sqrt
// (ça revient à calculer la longueur de l’hypoténuse dans un triangle
// où un des côtés fait 1, et l’autre est proportionnel à l’angle du rayon)


void	ray_casting(t_game *game)
{
	float start_x;
	float fraction;

	start_x = game->player.angle - PI / 6;
	fraction = PI / 3 / game->win_width;
	int i = 0;
	while (i < game->win_width)
	{
		draw_ray(&game->player, game, start_x, i);
		start_x += fraction;
		i++;
	}
}