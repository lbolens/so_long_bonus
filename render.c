/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:09:17 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/27 15:08:39 by lbolens          ###   ########.fr       */
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

static void manage_movements(t_game *game, int i, int j)
{
    char *moves;
    int middle;

    moves = ft_itoa(game->player.moves);
    middle = number_columns(game->map.map[i]) / 2;
    
    if (ft_strlen_2(moves) == 1)
    {
        if (j == middle + 1)
            manage_units_for_units(game, moves, i, j);
    }
    else if (ft_strlen_2(moves) == 2)
    {
        if (j == middle + 1)
            manage_tens_for_tens(game, moves, i, j);
        else if (j == middle + 2)
            manage_units_for_tens(game, moves, i, j);
    }
    else if (ft_strlen_2(moves) == 3)
    {
        if (j == middle + 1)
            manage_hundreds_for_hundreds(game, moves, i, j);
        else if (j == middle + 2)
            manage_tens_for_hundreds(game, moves, i, j);
        else if (j == middle + 3)
            manage_units_for_hundreds(game, moves, i, j);
    }
    else if (ft_strlen_2(moves) == 4)
    {
        if (j == middle + 1)
            manage_thousands_for_thousands(game, moves, i, j);
        else if (j == middle + 2)
            manage_hundreds_for_thousands(game, moves, i, j);
        else if (j == middle + 3)
            manage_tens_for_thousands(game, moves, i, j);
        else if (j == middle + 4)
            manage_units_for_thousands(game, moves, i, j);
    }
    free(moves);
}

static void render_1(t_game *game, int i, int j)
{
    int middle;
    
    middle = number_columns(game->map.map[i]) / 2;
    if (i == 0)
    {
        if (j == middle - 1)
            mlx_put_image_to_window(game->mlx, game->window, game->images.img_s, j * TILE_SIZE, i * TILE_SIZE);
        else if (j == middle - 2)
            mlx_put_image_to_window(game->mlx, game->window, game->images.img_e, j * TILE_SIZE, i * TILE_SIZE);
        else if (j == middle - 3)
            mlx_put_image_to_window(game->mlx, game->window, game->images.img_v, j * TILE_SIZE, i * TILE_SIZE);
        else if (j == middle - 4)
            mlx_put_image_to_window(game->mlx, game->window, game->images.img_o, j * TILE_SIZE, i * TILE_SIZE);
        else if (j == middle - 5)
            mlx_put_image_to_window(game->mlx, game->window, game->images.img_m, j * TILE_SIZE, i * TILE_SIZE);
        else if (j == middle)
            mlx_put_image_to_window(game->mlx, game->window, game->images.img_points, j * TILE_SIZE, i * TILE_SIZE);
        else if ((j == middle + 1 || j == middle + 2 || j == middle + 3 || j == middle + 4))
            manage_movements(game, i, j);
        else
            mlx_put_image_to_window(game->mlx, game->window, game->images.img_1x1, j * TILE_SIZE, i * TILE_SIZE);
    }
    else
        mlx_put_image_to_window(game->mlx, game->window, game->images.img_wall, j * TILE_SIZE, i * TILE_SIZE);
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
                render_1(game, i, j);
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
    char **map;
    
    map = game->map.map;
    doing_render(game, map, i, j);
}