/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:53:40 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/15 15:05:44 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static void manage_keycode(t_game *game, int keycode, int* new_x, int* new_y)
{
    if (!game || !new_x || !new_y)
        return;
        
    *new_x = game->player_x;
    *new_y = game->player_y;
    if (keycode == KEY_W || keycode == KEY_UP)
        *new_y -= 1;
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        *new_y += 1;
    else if (keycode == KEY_A || keycode == KEY_LEFT)
        *new_x -= 1;
    else if (keycode == KEY_D || keycode == KEY_RIGHT)
        *new_x += 1;
    else if (keycode == KEY_ESC)
    {
        destroy_game(game);
        exit(0);
    }
}

static int manage_conditions(t_game *game, char **map, int new_x, int new_y)
{
    char next_tile;

    if (!game || !map || new_x < 0 || new_y < 0 || !map[new_y])
        return (0);
        
    next_tile = map[new_y][new_x];
    if (next_tile == '1')
        return (0);
    if (next_tile == 'C')
    {
        game->collected++;
        map[new_y][new_x] = '0';
    }
    if (next_tile == 'E')
    {
        if (game->collected == game->total_collectibles)
        {
            printf("Victory!\n");
            destroy_game(game);
            exit(0);
        }
        return (0); 
    }
    return (1);
}

int key_handler(int keycode, t_game *game)
{
    char **map;
    int new_x;
    int new_y;

    if (!game || !game->map)
        return (0);
        
    map = game->map;
    new_x = game->player_x;
    new_y = game->player_y;
    
    manage_keycode(game, keycode, &new_x, &new_y);
    
    if (new_y < 0 || new_x < 0 || !map[new_y] || !map[new_y][new_x])
        return (0);
        
    if (manage_conditions(game, map, new_x, new_y) == 0)
        return (0);
        
    map[game->player_y][game->player_x] = '0';
    game->last_x = game->player_x;
    game->last_y = game->player_y;
    game->player_x = new_x;
    game->player_y = new_y;
    map[new_y][new_x] = 'P';
    game->moves++;
    printf("Moves: %d\n", game->moves);
    render_map(game, 0, 0);
    return (0);
}
