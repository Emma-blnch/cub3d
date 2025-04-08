/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:08:25 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/04/08 11:47:30 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	nswe_texture_config(char *line, t_game *data, t_check *check)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		check_duplicate(&check->found_no, data, "NO");
		check_texture_path(line, data, "NO");
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		check_duplicate(&check->found_so, data, "SO");
		check_texture_path(line, data, "SO");
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		check_duplicate(&check->found_we, data, "WE");
		check_texture_path(line, data, "WE");
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		check_duplicate(&check->found_ea, data, "EA");
		check_texture_path(line, data, "EA");
	}
}

static void	handle_texture_config(char *line, t_game *data, t_check *check)
{
	if (!ft_strncmp(line, "NO ", 3)  || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		nswe_texture_config(line, data, check);
	else if (ft_strncmp(line, "SP ", 3) == 0)
		check_texture_path(line, data, "SP");
	else if (ft_strncmp(line, "DO ", 3) == 0)
		check_texture_path(line, data, "DO");
	else
		error_exit(data, "Error: Unknown texture identifier");
}

static void	handle_color_config(char *line, t_game *data, t_check *check)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		check_duplicate(&check->found_f, data, "F");
		check_color_format(line, data, 'F');
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		check_duplicate(&check->found_c, data, "C");
		check_color_format(line, data, 'C');
	}
	else
		error_exit(data, "Error: Unknown color identifier");
}

static void	handle_config_line(char *line, t_game *data, t_check *check)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "DO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "SP ", 3) == 0)
		handle_texture_config(line, data, check);
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		handle_color_config(line, data, check);
	else
		error_exit(data, "Error: Unknown identifier");
}

void	check_file_config(t_game *data, char **lines)
{
	t_check		check;
	int			i;
	
	i = 0;
	ft_memset(&check, 0, sizeof(t_check));
	while (lines[i])
	{
		if (ft_str_is_whitespace(lines[i]))
		{
			i++;
			continue ;
		}
        if (ft_strchr(" 0123", lines[i][0]))
			break ;
		handle_config_line(lines[i], data, &check);
		i++;
	}
	if (!check.found_no || !check.found_so || !check.found_we
			|| !check.found_ea || !check.found_f || !check.found_c)
		error_exit(data, "Error: Missing configuration element");
}
