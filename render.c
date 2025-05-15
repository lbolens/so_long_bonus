/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:41:41 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/15 17:02:32 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

void render_map(t_game *game, int i, int j)
{
    char **map;
    char *move_str = ft_itoa(game->moves);
    char *display = ft_strjoin("Moves: ", move_str);

    if (!game || !game->map || !game->mlx || !game->window)
        return;
    if (!move_str || !display)
    {
        free(move_str);
        free(display);
        return;
    }

    map = game->map;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            mlx_put_image_to_window(game->mlx, game->window, game->img_floor, j * TILE_SIZE, i * TILE_SIZE);

            if (map[i][j] == '1')
                mlx_put_image_to_window(game->mlx, game->window, game->img_wall, j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == 'C')
                mlx_put_image_to_window(game->mlx, game->window, game->img_collectible, j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == 'E')
                    mlx_put_image_to_window(game->mlx, game->window, game->img_exit, j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == 'P')
            {
                if (game->moves == 0)
                    mlx_put_image_to_window(game->mlx, game->window, game->img_player_down, j * TILE_SIZE, i * TILE_SIZE);
                else if (game->player_y < game->last_y)
                    mlx_put_image_to_window(game->mlx, game->window, game->img_player_up, j * TILE_SIZE, i * TILE_SIZE);
                else if (game->player_y > game->last_y)
                    mlx_put_image_to_window(game->mlx, game->window, game->img_player_down, j * TILE_SIZE, i * TILE_SIZE);
                else if (game->player_x > game->last_x)
                    mlx_put_image_to_window(game->mlx, game->window, game->img_player_right, j * TILE_SIZE, i * TILE_SIZE);
                else if (game->player_x < game->last_x)
                    mlx_put_image_to_window(game->mlx, game->window, game->img_player_left, j * TILE_SIZE, i * TILE_SIZE);
                else
                    mlx_put_image_to_window(game->mlx, game->window, game->img_player_down, j * TILE_SIZE, i * TILE_SIZE);
            }
            j++;
        }
        i++;
    }
    mlx_string_put(game->mlx, game->window, 10, 20, 0xFFFFFF, display);
    free(move_str);
    free(display);
}

