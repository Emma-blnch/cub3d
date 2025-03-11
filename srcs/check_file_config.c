/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:08:25 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/11 16:15:53 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_texture_path(char *line, t_game *data, char *id)
{
	char	*path;

	path = ft_strchr(line, ' ');
	if (!path || !*(path + 1))
	{
		ft_printf("Error: Missing path for %s\n", id);
		error_exit(data, NULL);
	}
	path++;
	while (*path == ' ')
		path++;
	if (!*path)
	{
		ft_printf("Error: Empty path for %s\n", id);
		error_exit(data, NULL);
	}
	// Option bonus : vérifier que le fichier existe
	// int fd = open(path, O_RDONLY);
	// if (fd < 0)
	//     error_exit(data, "Error: Texture path is invalid");
	// close(fd);
}

static int	is_valid_rgb_value(char *str)
{
	int	val;

	if (!str || !*str)
		return (0);
	val = ft_atoi(str);
	if (val < 0 || val > 255)
		return (0);
	return (1);
}

static void	check_color_format(char *line, t_game *data, char id)
{
	char	**split;
	int		i;

	line += 2;
	split = ft_split(line, ',');
	if (!split)
		error_exit(data, "Error: Failed to split color line");
	i = 0;
	while (split[i])
		i++;
	if (i != 3 || !is_valid_rgb_value(split[0])
		|| !is_valid_rgb_value(split[1])
		|| !is_valid_rgb_value(split[2]))
	{
		free_split(split);
		error_exit(data, (id == 'F') ? "Error: Invalid floor color"
									: "Error: Invalid ceiling color");
	}
	free_split(split);
}

static void	check_duplicate(int *flag, t_game *data, char *id)
{
	if (*flag)
	{
		ft_printf("Error: Duplicate %s\n", id);
		error_exit(data, NULL);
	}
	*flag = 1;
}

// static void	handle_config_line(char *line, t_game *data, t_check *check)
// {
// 	if (ft_strncmp(line, "NO ", 3) == 0)
//     {
//         check_duplicate(&check->found_no, data, "NO");
//         check_texture_path(line, data, "NO");
//     }
// 	else if (ft_strncmp(line, "SO ", 3) == 0)
//     {
// 		check_duplicate(&check->found_so, data, "SO");
//         check_texture_path(line, data, "SO");
//     }
// 	else if (ft_strncmp(line, "WE ", 3) == 0)
//     {
// 		check_duplicate(&check->found_we, data, "WE");
//         check_texture_path(line, data, "WE");
//     }
// 	else if (ft_strncmp(line, "EA ", 3) == 0)
//     {
// 		check_duplicate(&check->found_ea, data, "EA");
//         check_texture_path(line, data, "EA");
//     }
// 	else if (ft_strncmp(line, "F ", 2) == 0)
//     {
// 		check_duplicate(&check->found_f, data, "F");
//         check_color_format(line, data, 'F');
//     }
// 	else if (ft_strncmp(line, "C ", 2) == 0)
//     {
// 		check_duplicate(&check->found_c, data, "C");
//         check_color_format(line, data, 'C');
//     }
// 	else
// 		error_exit(data, "Error: Unknown identifier");
// }

static void	handle_texture_config(char *line, t_game *data, t_check *check)
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
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		handle_texture_config(line, data, check);
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		handle_color_config(line, data, check);
	else
    {
        ft_printf("[DEBUG] Unknown line: %s", line);
		error_exit(data, "Error: Unknown identifier");
    }
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
        ft_printf("[DEBUG] parsing line %d: %s\n", i, lines[i]);
        if (ft_strchr(" 01NSEW", lines[i][0]))
			break ;
		handle_config_line(lines[i], data, &check);
		i++;
	}
    ft_printf("[DEBUG] Flags: NO:%d SO:%d WE:%d EA:%d F:%d C:%d\n",
        check.found_no, check.found_so, check.found_we,
        check.found_ea, check.found_f, check.found_c);
	if (!check.found_no || !check.found_so || !check.found_we
			|| !check.found_ea || !check.found_f || !check.found_c)
		error_exit(data, "Error: Missing configuration element");
	ft_printf("[DEBUG] check_file_config OK\n");
}
