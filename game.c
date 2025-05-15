/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:59:07 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/15 14:40:15 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

void    init_game(t_game *game, char** map)
{
    game->map_height = number_lines(map);
    game->map_width = number_columns(map[0]);
    game->player_x = -1;
    game->player_y = -1;
    game->last_x = -1;
    game->last_y = -1;
    find_player_position(map, &game->player_x, &game->player_y);
    game->total_collectibles = number_collectibles(map);
    game->collected = 0;
    game->moves = 0;
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error: Failed to initialize MLX\n");
        exit(1);
    }
    init_images(game);
}
