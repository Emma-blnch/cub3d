#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/cub3d.h"

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

    printf("[DEBUG] check_color_format received line = %s\n", line);
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
    printf("[DEBUG] check_color_format DONE, line = %s\n", line);
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
        ft_printf("[DEBUG] Après check_color_format: lines[i] = %s\n", line);
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
    printf("[TEST] pointer de lines = %p\n", (void *)lines);
    printf("[TEST] pointer de lines[0] = %p\n", (void *)lines[0]);

    printf("[DEBUG] Avant boucle : lines[0] = %s\n", lines[0]);
	while (lines[i])
	{
		if (ft_str_is_whitespace(lines[i]))
		{
			i++;
			continue ;
		}
        printf("[DEBUG] parsing line %d: %s\n", i, lines[i]);
        if (ft_strchr(" 01", lines[i][0]))
			break ;
		handle_config_line(lines[i], data, &check);
        printf("[DEBUG] Après handle_config_line : lines[i] = %s\n", lines[i]);
		i++;
	}
    printf("[DEBUG] Flags: NO:%d SO:%d WE:%d EA:%d F:%d C:%d\n",
        check.found_no, check.found_so, check.found_we,
        check.found_ea, check.found_f, check.found_c);
	if (!check.found_no || !check.found_so || !check.found_we
			|| !check.found_ea || !check.found_f || !check.found_c)
		error_exit(data, "Error: Missing configuration element");
	printf("[DEBUG] check_file_config OK\n");
}

//  ---------- TEST CHECK COMPLET ------
// int	main(void)
// {
// 	t_game	data;
// 	char	**lines;

// 	ft_memset(&data, 0, sizeof(t_game));

// 	lines = malloc(sizeof(char *) * 9);
// 	if (!lines)
// 		return (1);
// 	lines[0] = ft_strdup("NO ./textures/north.xpm\n");
// 	lines[1] = ft_strdup("SO ./textures/south.xpm\n");
// 	lines[2] = ft_strdup("WE ./textures/west.xpm\n");
// 	lines[3] = ft_strdup("EA ./textures/east.xpm\n");
// 	lines[4] = ft_strdup("F 220,100,0\n");
// 	lines[5] = ft_strdup("C 225,30,0\n");
// 	lines[6] = ft_strdup("\n");
// 	lines[7] = ft_strdup("111111\n");
// 	lines[8] = NULL;

// 	printf("[TEST] BEFORE check_file_config\n");
//     ft_printf("[MAIN] pointer de lines = %p\n", (void *)lines);
//     ft_printf("[MAIN] pointer de lines[0] = %p\n", (void *)lines[0]);
// 	check_file_config(&data, lines);
// 	printf("[TEST] AFTER check_file_config\n");

// 	free_lines(lines);
// 	return (0);
// }


// ------------ TEST ALLOC --------------
// int	main(void)
// {
// 	char **lines = malloc(sizeof(char *) * 3);
// 	if (!lines)
// 		return (1);

// 	lines[0] = strdup("NO ./textures/north.xpm\n");
// 	lines[1] = strdup("SO ./textures/south.xpm\n");
// 	lines[2] = NULL;

// 	printf("[TEST] lines[0] = %s", lines[0]);
// 	printf("[TEST] lines[1] = %s", lines[1]);

// 	free(lines[0]);
// 	free(lines[1]);
// 	free(lines);
// }

// ------------ TEST CHECK FILE CONFIG ------------
int	main(void)
{
	t_game	data;
	char	**lines;

	ft_memset(&data, 0, sizeof(t_game));

	lines = malloc(sizeof(char *) * 9);
	if (!lines)
	{
		printf("Malloc failed\n");
		return (1);
	}
	lines[0] = ft_strdup("NO ./textures/north.xpm\n");
	lines[1] = ft_strdup("SO ./textures/south.xpm\n");
	lines[2] = ft_strdup("WE ./textures/west.xpm\n");
	lines[3] = ft_strdup("EA ./textures/east.xpm\n");
	lines[4] = ft_strdup("F 220,100,0\n");
	lines[5] = ft_strdup("C 225,30,0\n");
	lines[6] = ft_strdup("\n");
	lines[7] = ft_strdup("111111\n"); // début de map
	lines[8] = NULL;

	check_file_config(&data, lines);
	printf("[TEST] check_file_config OK ✅\n");

	free_lines(lines);
	return (0);
}


// ------------ TEST HANDLE CONFIG LINE ------------
// int main(void)
// {
// 	t_game data;
// 	t_check check;
// 	char *line1 = ft_strdup("NO ./textures/north.xpm\n");
// 	char *line2 = ft_strdup("SO ./textures/south.xpm\n");
// 	char *line3 = ft_strdup("F 220,100,0\n");
// 	char *line4 = ft_strdup("C 255,255,255\n");

// 	ft_memset(&data, 0, sizeof(t_game));
// 	ft_memset(&check, 0, sizeof(t_check));

// 	handle_config_line(line1, &data, &check);
// 	handle_config_line(line2, &data, &check);
// 	handle_config_line(line3, &data, &check);
// 	handle_config_line(line4, &data, &check);

// 	printf("[TEST] Config parsed with flags : NO:%d SO:%d WE:%d EA:%d F:%d C:%d\n",
// 		check.found_no, check.found_so, check.found_we,
// 		check.found_ea, check.found_f, check.found_c);

// 	free(line1);
// 	free(line2);
// 	free(line3);
// 	free(line4);
// 	return (0);
// }
