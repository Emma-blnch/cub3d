/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:49:54 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/24 09:41:34 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

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

typedef struct s_player {
    int         x; // position int sur la carte
    int         y;
    float       pos_x; // position float sur la carte (pour les déplacements)
    float       pos_y;
    char        dir;
    
    float   angle;
    bool    key_up;
    bool    key_down;
    bool    key_left;
    bool    key_right;

    bool    left_rotate;
    bool    right_rotate;
}               t_player;

typedef struct s_game {
    t_mlx       mlx;
    t_config    config;
    t_ray       ray;
    t_hud       hud;
    t_player    player;
    int         win_width;
    int         win_height;
    bool         menu_active;
	bool         menu_selection;
}               t_game;

typedef struct s_check {
    bool            found_no;
	bool	        found_so;
	bool	        found_we;
	bool	        found_ea;
	bool	        found_f;
	bool	        found_c;
}               t_check;

#endif