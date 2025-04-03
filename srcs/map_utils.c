/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:34:50 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/04/03 08:57:40 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	has_wall_start(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			return (1);
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (0);
}

int	set_color(char **map, int y, int x)
{
	int		color;

	color = -1;
	if (map[y][x] == '1')
		color = 0x555555;
	else if (map[y][x] == '0')
		color = 0xFFFFFF;
	else if (ft_strchr("NSEW", map[y][x]))
		color = 0xFFFFFF;
	return (color);
}

int	get_mini_tile_size(t_game *game)
{
	int	max_cols;
	int	nb_rows;
	int	tile;
	int	len;
	int	height_tile;

	max_cols = 0;
	nb_rows = 0;
	while (game->config.map[nb_rows])
	{
		len = ft_strlen(game->config.map[nb_rows]);
		if (len > max_cols)
			max_cols = len;
		nb_rows++;
	}
	tile = (int)(game->win_width * 0.2 / max_cols);
	height_tile = (int)(game->win_height * 0.2 / nb_rows);
	if (height_tile < tile)
		tile = height_tile;
	if (tile < 1)
		tile = 1;
	return (tile);
}
