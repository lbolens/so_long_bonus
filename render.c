/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:41:41 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/18 17:07:39 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void render_1(t_game *game, int i, int j)
{
    if (i == 0 && j == 0)
        mlx_put_image_to_window(game->mlx, game->window, game->images.img_1x1, j * TILE_SIZE, i * TILE_SIZE);
    else
        mlx_put_image_to_window(game->mlx, game->window, game->images.img_wall, j * TILE_SIZE, i * TILE_SIZE);
}

static void doing_render(t_game* game, char** map, int i, int j)
{
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            mlx_put_image_to_window(game->mlx, game->window, game->images.img_floor, j * TILE_SIZE, i * TILE_SIZE);
            if (map[i][j] == '1')
                render_1(game, i, j);
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
    char **map;
    char *move_str;
    char *display;

    move_str = ft_itoa(game->player.moves);
    display = ft_strjoin("Moves: ", move_str);
    if (!game || !game->map.map || !game->mlx || !game->window)
        return;
    if (!move_str || !display)
    {
        free(move_str);
        free(display);
        return;
    }
    map = game->map.map;
    doing_render(game, map, i, j);
    mlx_string_put(game->mlx, game->window, 10, 20, 0xFFFFFF, display);
    free(move_str);
    free(display);
}

