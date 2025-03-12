/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:36:11 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/12 12:17:24 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_filename(t_game *data, char *filename)
{
	int	i;

	i = 0;
	if (!filename || !*filename)
		error_exit(data, "Error: Empty file name");
	while (filename[i])
		i++;
	i--;
	while (i >= 0 && filename[i] != '.')
		i--;
	if (i < 0 || ft_strcmp(filename + i, ".cub") != 0)
		error_exit(data, "Error: file must have <.cub> extension");
}

char	**read_all_lines(char *filename, t_game *data)
{
	int		fd;
	char	*line;
	char	**lines;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(data, "Error: Cannot read file");
	lines = malloc(sizeof(char *) * (MAX_LINES + 1));
	if (!lines)
		error_exit(data, "Error: Malloc failed");
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i >= MAX_LINES)
			error_exit(data, "Error: File too big");
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

void	validate_file(char *filename, t_game *data)
{
	char	**lines;

	check_filename(data, filename);
	lines = read_all_lines(filename, data);
	if (!lines || count_lines(lines) < 9)
		error_exit(data, "Error: File too short");
	check_file_config(data, lines);
	check_map(data, lines);
	store_data(data, lines);
	free_lines(lines);
}
