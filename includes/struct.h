/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:49:54 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/23 09:50:07 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <stdbool.h>

typedef struct s_mlx {
    void        *mlx_ptr;
    void        *win_ptr;
    void        *img;
    char        *addr;
    int         bpp;
    int         line_length;
    int         endian;
}               t_mlx;

typedef struct s_config {
    char        *no_path;
    char        *so_path;
    char        *we_path;
    char        *ea_path;
    int         floor_color;
    int         ceiling_color;
    char        **map;
    int         player_x;
    int         player_y;
    char        player_dir;
}               t_config;

typedef struct s_ray {
    double      ray_dir_x;
    double      ray_dir_y;
    int         map_x;
    int         map_y;
    double      side_dist_x;
    double      side_dist_y;
    double      delta_dist_x;
    double      delta_dist_y;
    double      perp_wall_dist;
    int         step_x;
    int         step_y;
    int         hit;
    int         side;
}               t_ray;

typedef struct s_hud {
	void	    *gun_img;
	int		    gun_w;
	int		    gun_h;
    void	    *menu_bg;
    int		    menu_bg_w;
    int		    menu_bg_h;
    void	    *wall;
    int		    wall_w;
    int		    wall_h;
}	        t_hud;

typedef struct s_player
{
    float       x;
    float       y;
    float       angle;
    bool        key_up;
    bool        key_down;
    bool        key_left;
    bool        key_rigth;
    bool        left_rotate;
    bool        right_rotate;
}               t_player;

typedef struct s_game {
    t_mlx       mlx;
    t_config    config;
    t_ray       ray;
    t_hud       hud;
    t_player    player;
    double      pos_x;
    double      pos_y;
    double      dir_x;
    double      dir_y;
    double      plane_x;
    double      plane_y;
    int         win_width;
    int         win_height;
    int         menu_active; // 1 si on est dans le menu, 0 si on est en jeu
	int         menu_selection; // 0 = Play, 1 = Exit
}               t_game;

typedef struct s_check {
    int         found_no;
	int	        found_so;
	int	        found_we;
	int	        found_ea;
	int	        found_f;
	int	        found_c;
}               t_check;

#endif