/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:28:48 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/15 12:27:20 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

void    init_images(t_game *game)
{
    int w;
    int h;
    
    if (!game || !game->mlx)
        return;
    w = TILE_SIZE;
    h = TILE_SIZE;
    game->img_wall = NULL;
    game->img_collectible = NULL;
    game->img_floor = NULL;
    game->img_player_up = NULL;
    game->img_player_down = NULL;
    game->img_player_left = NULL;
    game->img_player_right = NULL;
    game->img_exit = NULL;
    game->img_wall = mlx_xpm_file_to_image(game->mlx, "textures/test_wall.xpm", &w, &h);
    game->img_collectible = mlx_xpm_file_to_image(game->mlx, "textures/test_collectible.xpm", &w, &h);
    game->img_floor = mlx_xpm_file_to_image(game->mlx, "textures/test_floor.xpm", &w, &h);
    game->img_player_up = mlx_xpm_file_to_image(game->mlx, "textures/tuile_player_up.xpm", &w, &h);
    game->img_player_down = mlx_xpm_file_to_image(game->mlx, "textures/tuile_player_down.xpm", &w, &h);
    game->img_player_left = mlx_xpm_file_to_image(game->mlx, "textures/tuile_player_left.xpm", &w, &h);
    game->img_player_right = mlx_xpm_file_to_image(game->mlx, "textures/tuile_player_right.xpm", &w, &h);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "textures/test_exit.xpm", &w, &h);
    if (!game->img_wall || !game->img_collectible || !game->img_floor || !game->img_player_up || !game->img_player_down || !game->img_player_left || !game->img_player_right || !game->img_exit)
    {
        printf("Error: Failed to load images. Please check if all image files exist in the textures directory.\n");
        destroy_game(game);
        exit(1);
    }
}
