/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:00:43 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/24 00:54:01 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
