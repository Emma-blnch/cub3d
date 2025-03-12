/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:00:43 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/12 12:41:50 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_player_position(t_game *data)
{
	int	y;
	int	x;
	char	**map;
    
    map = data->config.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				if (data->config.player_dir)
					error_exit(data, "Error: Multiple player positions found");
				data->config.player_x = x;
				data->config.player_y = y;
				data->config.player_dir = map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
	error_exit(data, "Error: No player position found");
}

void	print_map(char **map)
{
	int	i = 0;

	printf("[DEBUG] Map content:\n");
	while (map[i])
	{
		printf("Line %d: %s", i, map[i]); // les lignes contiennent déjà '\n'
		i++;
	}
}

void	store_map(t_game *data, char **lines)
{
	int		start;
	int		map_lines;
	int		i;
	int		j;

	start = find_map_start_index(lines);
	map_lines = 0;
	i = start;
	while (lines[i])
	{
		if (!ft_str_is_whitespace(lines[i++]))
			map_lines++;
	}
	data->config.map = malloc(sizeof(char *) * (map_lines + 1));
	if (!data->config.map)
		error_exit(data, "Error: Failed to allocate memory for map");
	i = start;
	j = 0;
	while (lines[i])
	{
		if (!ft_str_is_whitespace(lines[i]))
			data->config.map[j++] = ft_strdup(lines[i]);
		i++;
	}
	data->config.map[j] = NULL;
}

void    store_data(t_game *data, char **lines)
{
    parse_textures(data, lines);
    parse_colors(data, lines);
    store_map(data, lines);
    store_player_position(data);
}
