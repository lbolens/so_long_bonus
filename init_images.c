/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:28:48 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/18 13:25:42 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static void init_map_images(t_game *game)
{
    int w;
    int h;
    
    w = TILE_SIZE;
    h = TILE_SIZE;
    game->images.img_wall = NULL;
    game->images.img_collectible = NULL;
    game->images.img_floor = NULL;
    game->images.img_exit = NULL;
    game->images.img_1x1 = NULL;
    game->images.img_asteroid = NULL;
    game->images.img_1x1 = mlx_xpm_file_to_image(game->mlx, "textures/tuile_1x1.xpm", &w, &h);
    game->images.img_wall = mlx_xpm_file_to_image(game->mlx, "textures/tuile_wall.xpm", &w, &h);
    game->images.img_collectible = mlx_xpm_file_to_image(game->mlx, "textures/tuile_collectible.xpm", &w, &h);
    game->images.img_floor = mlx_xpm_file_to_image(game->mlx, "textures/tuile_floor.xpm", &w, &h);
    game->images.img_exit = mlx_xpm_file_to_image(game->mlx, "textures/tuile_exit.xpm", &w, &h);
    game->images.img_asteroid = mlx_xpm_file_to_image(game->mlx, "textures/tuile_asteroid.xpm", &w, &h);
    game->images.img_game_over = mlx_xpm_file_to_image(game->mlx, "textures/tuile_game_over.xpm", &w, &h);
    game->images.img_victory = mlx_xpm_file_to_image(game->mlx, "textures/tuile_victory.xpm", &w, &h);
    if (!game->images.img_wall || !game->images.img_collectible || !game->images.img_floor || !game->images.img_exit || !game->images.img_asteroid)
    {
        printf("Error: Failed to load images. Please check if all image files exist in the textures directory.\n");
        destroy_game(game);
        exit(1);
    }
}

static void init_player_images(t_game *game)
{
    int w;
    int h;

    w = TILE_SIZE;
    h = TILE_SIZE;
    game->images.img_player_up = NULL;
    game->images.img_player_down = NULL;
    game->images.img_player_left = NULL;
    game->images.img_player_right = NULL;
    game->images.img_player_up = mlx_xpm_file_to_image(game->mlx, "textures/tuile_player_up.xpm", &w, &h);
    game->images.img_player_down = mlx_xpm_file_to_image(game->mlx, "textures/tuile_player_down.xpm", &w, &h);
    game->images.img_player_left = mlx_xpm_file_to_image(game->mlx, "textures/tuile_player_left.xpm", &w, &h);
    game->images.img_player_right = mlx_xpm_file_to_image(game->mlx, "textures/tuile_player_right.xpm", &w, &h);
    if (!game->images.img_player_up || !game->images.img_player_down || !game->images.img_player_left || !game->images.img_player_right)
    {
        printf("Error: Failed to load images. Please check if all image files exist in the textures directory.\n");
        destroy_game(game);
        exit(1);
    }
}

void    init_images(t_game *game)
{
    if (!game || !game->mlx)
        return;
    init_map_images(game);
    init_player_images(game);
}
