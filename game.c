/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:59:07 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/17 14:32:40 by lbolens          ###   ########.fr       */
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
    game->asteroid = NULL; // Initialisation de la liste d'astéroïdes à NULL
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error: Failed to initialize MLX\n");
        exit(1);
    }
    init_images(game);
    init_seed_from_map(game); // Initialisation de la graine aléatoire
}

int game_loop(t_game *game)
{
	static int frame = 0;

	frame++;

	if (frame % 60 == 0) // toutes les ~1 seconde
		init_asteroid(game);

	update_asteroids(game);

	render_map(game, 0, 0);          // ta map
	render_asteroids(game);    // les astéroïdes en plus

	return (0);
}
