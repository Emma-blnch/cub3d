/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:52:09 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/22 13:06:57 by aelaen           ###   ########.fr       */
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
// # include <X11/keysym.h>

# define MAX_LINES 1024
# define ESC_KEY 65307
# define TILE_SIZE 10

# define RESET		"\033[0m"
# define R		    "\033[31m"
# define G		    "\033[32m"
# define Y		    "\033[33m"
# define B		    "\033[34m"

// TOUCHES LINUX
// # define XK_Up 65362
// # define XK_w 119
// # define XK_Down 65364
// # define XK_s 115
// # define XK_Escape 65307
// # define XK_Return 65293
// # define XK_E 101

// TOUCHES MACOS
# define XK_Up 126
# define XK_w 6
# define XK_Down 125
# define XK_s 1
# define XK_Escape 53
# define XK_E 14

#define XK_Left                          124  /* Move left, left arrow */
#define XK_Right                         123  /* Move right, right arrow */

// int     main(int argc, char **argv);

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

// Utils
int     count_lines(char **lines);
int     ft_strcmp(char *s1, char *s2);
void	free_split(char **split);
int     ft_str_is_whitespace(char *str);
int     is_valid_map_line(char *line);
int     has_wall_start(char *line);
void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color);

// Error and free
void	error_exit(t_game *data, char *message);
void    free_map(char **map);
void    free_resources(t_game *data);
void	free_lines(char **lines);

#endif