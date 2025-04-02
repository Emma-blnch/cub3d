/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:49:54 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/04/02 11:11:11 by eblancha         ###   ########.fr       */
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
    float      start_x;
    float      start_y;
    float      dir_x;
    float      dir_y;
    int         map_x;
    int         map_y;
    float      side_x;
    float      side_y;
    float      delta_x;
    float      delta_y;
    float      perp_wall_dist;
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

typedef struct s_img {
    void        *img;
    char        *addr;
    int         bpp;
    int         line_length;
    int         endian;
    int         width;
    int         height;
}               t_img;

typedef struct s_texture {
    t_img       no;
    t_img       so;
    t_img       we;
    t_img       ea;
}               t_texture;

typedef struct s_game {
    t_mlx       mlx;
    t_config    config;
    t_ray       ray;
    t_hud       hud;
    t_player    player;
    t_texture   tex;
    double      pos_x;
    double      pos_y;
    double      dir_x;
    double      dir_y;
    double      plane_x;
    double      plane_y;
    int         win_width;
    int         win_height;
    int         menu_active;
	int         menu_selection;
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