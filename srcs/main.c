/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:51:51 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/03/12 12:17:15 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*init_data(void)
{
	t_game	*data;

	data = malloc(sizeof(t_game));
	if (!data)
		error_exit(NULL, "Error: Struct init failed");
	ft_memset(data, 0, sizeof(t_game));
	return (data);
}

int			main(int argc, char **argv)
{
    t_game    *data;
    
    data = NULL;
    if (argc != 2)
        error_exit(data, "Usage: ./cub3d <map.cub>");
    data = init_data();
    validate_file(argv[1], data);
    // init_window(data);
    // game_loop();
    free_resources(data);
    return (0);
}

// 111111
// 100001
// 10N  1
// 100 01
// 111 11