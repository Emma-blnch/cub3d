/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:51:51 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/04/05 13:48:38 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*init_data(int argc, char **argv)
{
	t_game	*data;

	data = malloc(sizeof(t_game));
	if (!data)
		error_exit(NULL, "Error: Struct init failed");
	ft_memset(data, 0, sizeof(t_game));
    data->menu_active = 1;
    data->menu_selection = 0;
    // a garder ?
    if (argc == 4)
    {
        data->win_width = ft_atoi(argv[2]);
        data->win_height = ft_atoi(argv[3]);
    }
    else
    {
        data->win_width = 1280;
        data->win_height = 720;
    }
    if (data->win_width < 300 || data->win_height < 300
        || data->win_width > 1920 || data->win_height > 1080)
    {
        error_exit(data, "Error: Window size must be between 300x300 and 1920x1080");
    }
    data->z_buffer = malloc(sizeof(float) * data->win_width);
    if (!data->z_buffer)
        error_exit(data, "Error: Could not allocate z_buffer");
	return (data);
}

int			main(int argc, char **argv)
{
    t_game    *data;
    
    data = NULL;
    if (argc != 2 && argc != 4)
        error_exit(data, "Usage: ./cub3d <maps/map.cub> [<WIN WIDTH> <WIN HEIGHT>]");
    data = init_data(argc, argv);
    validate_file(argv[1], data);
    init_player(&data->player, data);
    init_window(data);
    free_resources(data);
    return (0);
}
