/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:10:27 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/12 11:52:49 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_characters(char **lines, int start, t_game *data)
{
	int	i;
	int	j;
	int	player_count;
    
    player_count = 0;
	i = start;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (!ft_strchr("01NSEW \n", lines[i][j]))
				error_exit(data, "Error: Invalid character in map");
			if (ft_strchr("NSEW", lines[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		error_exit(data, "Error: Map must contain exactly one player");
}

static int	find_map_start_index(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (!ft_str_is_whitespace(lines[i])
			&& ft_strchr("01", lines[i][0]))
			return (i);
		i++;
	}
	return (-1);
}

void	check_map(t_game *data, char **lines)
{
	int	start;
    
    start = find_map_start_index(lines);
	check_map_characters(lines, start, data);
	check_map_is_closed(lines, start, data);
}
