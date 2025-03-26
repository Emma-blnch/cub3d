/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:52:09 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/26 18:44:01 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

# define MAX_LINES 1024
# define ESC_KEY 65307
# define TILE_SIZE 64

# define PI 3.14159265359

# define RESET		"\033[0m"
# define R		    "\033[31m"
# define G		    "\033[32m"
# define Y		    "\033[33m"
# define B		    "\033[34m"

// TOUCHES MACOS
# define Up 126
# define W 13 // (Z) 6 pour W
# define Down 125
# define S 1
# define Escape 53
# define E 14
#define A 0 // (Q) 12 pour A
#define S 1
#define D 2
#define LEFT 123
#define RIGHT 124

// Init
t_game	*init_data(int argc, char **argv);

// Check file
void	validate_file(char *filename, t_game *data);
char	**read_all_lines(char *filename, t_game *data);
void	check_filename(t_game *data, char *filename);
void	check_file_config(t_game *data, char **lines);
void	check_map(t_game *data, char **lines);
void	check_map_is_closed(char **lines, int start, t_game *data);
void	check_duplicate(int *flag, t_game *data, char *id);
void	check_color_format(char *line, t_game *data, char id);
void	check_texture_path(char *line, t_game *data, char *id);
int     find_map_start_index(char **lines);

// Store data
void    store_data(t_game *data, char **lines);
void	parse_textures(t_game *data, char **lines);
void	parse_colors(t_game *data, char **lines);
void	store_player_position(t_game *data);

// Window
void	init_window(t_game *game);
void	draw_floor_and_ceiling(t_game *game);

// Menu
void	draw_menu(t_game *game);

// Mini-map
int     render(t_game *game);
void	draw_minimap(t_game *game);

// Player
void    move_player(t_player *player, t_game *game);
void    init_player(t_player *player, t_game *game);

// Events
int	close_window(t_game *data);
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);

// Utils
int     count_lines(char **lines);
int     ft_strcmp(char *s1, char *s2);
int     get_tile_size(t_game *game);
int     ft_str_is_whitespace(char *str);
int     is_valid_map_line(char *line);
int     has_wall_start(char *line);
void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color);
void	draw_square(int x, int y, int size, int color, t_game *game);
void	free_split(char **split);

// Error and free
void	error_exit(t_game *data, char *message);
void    free_map(char **map);
void    free_resources(t_game *data);
void	free_lines(char **lines);


bool    is_wall(float px, float py, char **map);

#endif