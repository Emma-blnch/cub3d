/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:52:09 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/11 16:10:21 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define MAX_LINES 1024
# define ESC_KEY 65307

# define RESET		"\033[0m"
# define R		    "\033[31m"
# define G		    "\033[32m"
# define Y		    "\033[33m"
# define B		    "\033[34m"


int     main(int argc, char **argv);

// Init
t_game	*init_data(void);

// Check file
void	validate_file(char *filename, t_game *data);
char	**read_all_lines(char *filename, t_game *data);
void	check_filename(t_game *data, char *filename);
void	check_file_config(t_game *data, char **lines);

// Window
// void	init_window(t_game *game);
// int     close_window(t_matrix *data);

// Utils
int     count_lines(char **lines);
int     ft_strcmp(char *s1, char *s2);
void	free_split(char **split);
int     ft_str_is_whitespace(char *str);

// Error and free
void	error_exit(t_game *data, char *message);
void    free_map(char **map);
void    free_resources(t_game *data);
void	free_lines(char **lines);

#endif