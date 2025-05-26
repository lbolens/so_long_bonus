/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:41:41 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/26 16:25:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

#include "so_long.h"
#include "mlx.h"

static void render_P(t_game *game, int i, int j)
{
    if (game->player.moves == 0)
        mlx_put_image_to_window(game->mlx, game->window, game->images.img_player_down, j * TILE_SIZE, i * TILE_SIZE);
    else if (game->player.y < game->player.last_y)
        mlx_put_image_to_window(game->mlx, game->window, game->images.img_player_up, j * TILE_SIZE, i * TILE_SIZE);
    else if (game->player.y > game->player.last_y)
        mlx_put_image_to_window(game->mlx, game->window, game->images.img_player_down, j * TILE_SIZE, i * TILE_SIZE);
    else if (game->player.x > game->player.last_x)
        mlx_put_image_to_window(game->mlx, game->window, game->images.img_player_right, j * TILE_SIZE, i * TILE_SIZE);
    else if (game->player.x < game->player.last_x)
        mlx_put_image_to_window(game->mlx, game->window, game->images.img_player_left, j * TILE_SIZE, i * TILE_SIZE);
    else
        mlx_put_image_to_window(game->mlx, game->window, game->images.img_player_down, j * TILE_SIZE, i * TILE_SIZE);
}
static void doing_render(t_game *game, char **map, int i, int j)
{
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '1')
            {
                if (i == 0)
                    mlx_put_image_to_window(game->mlx, game->window, game->images.img_1x1, j * TILE_SIZE, i * TILE_SIZE);
                else
                    mlx_put_image_to_window(game->mlx, game->window, game->images.img_wall, j * TILE_SIZE, i * TILE_SIZE);
            }
            else if (map[i][j] == '0')
                mlx_put_image_to_window(game->mlx, game->window, game->images.img_floor, j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == 'C')
                mlx_put_image_to_window(game->mlx, game->window, game->images.img_collectible, j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == 'E')
                mlx_put_image_to_window(game->mlx, game->window, game->images.img_exit, j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == 'P')
                render_P(game, i, j);
            j++;
        }
        i++;
    }
}

void render_map(t_game *game, int i, int j)
{
    char *move_str;
    char *display;
    char **map;
    
    map = game->map.map;
    move_str = ft_itoa(game->player.moves);
    if (!move_str)
        return;
    display = ft_strjoin("Moves: ", move_str);
    if (!display)
    {
        free(move_str);
        return;
    }
    doing_render(game, map, i, j);
    //mlx_string_put(game->mlx, game->window, 0, 0, 0xFFFFFF, display);
    free(move_str);
    free(display);
}
