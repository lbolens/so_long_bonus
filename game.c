/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:59:07 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/19 10:21:12 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

void    init_game(t_game *game, char** map)
{
    game->map.map_height = number_lines(map);
    game->map.map_width = number_columns(map[0]);
    game->player.x = -1;
    game->player.y = -1;
    game->player.last_x = -1;
    game->player.last_y = -1;
    find_player_position(map, &game->player.x, &game->player.y);
    game->map.total_collectibles = number_collectibles(map);
    game->player.collected = 0;
    game->player.moves = 0;
    game->asteroid = NULL;
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error: Failed to initialize MLX\n");
        exit(1);
    }
    init_images(game);
    init_seed_from_map(game);
}

int game_loop(t_game *game)
{
	static int frame = 0;

	frame++;

	if (frame % 40 == 0)
		init_asteroid(game);
	update_asteroids(game);
	render_map(game, 0, 0);
	render_asteroids(game);
	return (0);
}
