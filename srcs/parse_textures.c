/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:01:30 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/12 12:37:09 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*extract_path(char *line)
{
	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	return (ft_strdup(line));
}

void	parse_textures(t_game *data, char **lines)
{
	int	i = 0;

	while (lines[i])
	{
		if (lines[i][0] == '\n' || lines[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (ft_strchr("01 ", lines[i][0]))
			break ;
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
			data->config.no_path = extract_path(lines[i]);
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
			data->config.so_path = extract_path(lines[i]);
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
			data->config.we_path = extract_path(lines[i]);
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
			data->config.ea_path = extract_path(lines[i]);
		i++;
	}
}
