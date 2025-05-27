/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:28:48 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/27 13:40:01 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static void init_map_images(t_game *game, int w, int h)
{
    w = TILE_SIZE;
    h = TILE_SIZE;
    game->images.img_wall = NULL;
    game->images.img_collectible = NULL;
    game->images.img_floor = NULL;
    game->images.img_exit = NULL;
    game->images.img_1x1 = NULL;
    game->images.img_asteroid = NULL;
    game->images.img_floor = mlx_xpm_file_to_image(game->mlx, "textures/tuile_floor.xpm", &w, &h);
    game->images.img_1x1 = mlx_xpm_file_to_image(game->mlx, "textures/tuile_1x1.xpm", &w, &h);
    game->images.img_wall = mlx_xpm_file_to_image(game->mlx, "textures/tuile_wall.xpm", &w, &h);
    game->images.img_collectible = mlx_xpm_file_to_image(game->mlx, "textures/tuile_collectible.xpm", &w, &h);
    game->images.img_exit = mlx_xpm_file_to_image(game->mlx, "textures/tuile_exit.xpm", &w, &h);
    game->images.img_asteroid = mlx_xpm_file_to_image(game->mlx, "textures/tuile_asteroid.xpm", &w, &h);
    if (!game->images.img_asteroid || !game->images.img_floor || 
        !game->images.img_1x1 || !game->images.img_wall || 
        !game->images.img_collectible || !game->images.img_exit || 
        !game->images.img_asteroid)
    {
        printf("Error: Failed to load images\n");
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
    if (!game->images.img_player_up || !game->images.img_player_down || 
        !game->images.img_player_left || !game->images.img_player_right)
    {
        printf("Error: Failed to load tuile_player_up.xpm\n");
        destroy_game(game);
        exit(1);
    }
}

static void init_moves_images(t_game *game)
{
    int w;
    int h;

    w = TILE_SIZE;
    h = TILE_SIZE;
    game->images.img_m = NULL;
    game->images.img_o = NULL;
    game->images.img_v = NULL;
    game->images.img_e = NULL;
    game->images.img_s = NULL;
    game->images.img_points = NULL;
    game->images.img_m = mlx_xpm_file_to_image(game->mlx, "textures/img_m.xpm", &w, &h);
    game->images.img_o = mlx_xpm_file_to_image(game->mlx, "textures/img_o.xpm", &w, &h);
    game->images.img_v = mlx_xpm_file_to_image(game->mlx, "textures/img_v.xpm", &w, &h);
    game->images.img_e = mlx_xpm_file_to_image(game->mlx, "textures/img_e.xpm", &w, &h);
    game->images.img_s = mlx_xpm_file_to_image(game->mlx, "textures/img_s.xpm", &w, &h);
    game->images.img_points = mlx_xpm_file_to_image(game->mlx, "textures/img_points.xpm", &w, &h);
    if (!game->images.img_m || !game->images.img_o || 
        !game->images.img_v || !game->images.img_e || !game->images.img_s || !game->images.img_points)
    {
        printf("Error: Failed to load moves_images.xpm\n");
        destroy_game(game);
        exit(1);
    }
}

static void init_digits_images(t_game *game)
{
    int w;
    int h;

    w = TILE_SIZE;
    h = TILE_SIZE;
    game->images.img_0 = NULL;
    game->images.img_1 = NULL;
    game->images.img_2 = NULL;
    game->images.img_3 = NULL;
    game->images.img_4 = NULL;
    game->images.img_5 = NULL;
    game->images.img_6 = NULL;
    game->images.img_7 = NULL;
    game->images.img_8 = NULL;
    game->images.img_9 = NULL;
    game->images.img_0 = mlx_xpm_file_to_image(game->mlx, "textures/img_0.xpm", &w, &h);
    game->images.img_1 = mlx_xpm_file_to_image(game->mlx, "textures/img_1.xpm", &w, &h);
    game->images.img_2 = mlx_xpm_file_to_image(game->mlx, "textures/img_2.xpm", &w, &h);
    game->images.img_3 = mlx_xpm_file_to_image(game->mlx, "textures/img_3.xpm", &w, &h);
    game->images.img_4 = mlx_xpm_file_to_image(game->mlx, "textures/img_4.xpm", &w, &h);
    game->images.img_5 = mlx_xpm_file_to_image(game->mlx, "textures/img_5.xpm", &w, &h);
    game->images.img_6 = mlx_xpm_file_to_image(game->mlx, "textures/img_6.xpm", &w, &h);
    game->images.img_7 = mlx_xpm_file_to_image(game->mlx, "textures/img_7.xpm", &w, &h);
    game->images.img_8 = mlx_xpm_file_to_image(game->mlx, "textures/img_8.xpm", &w, &h);
    game->images.img_9 = mlx_xpm_file_to_image(game->mlx, "textures/img_9.xpm", &w, &h);
    if (!game->images.img_1 || !game->images.img_2 || 
        !game->images.img_3 || !game->images.img_4 || !game->images.img_5 || 
        !game->images.img_6 || !game->images.img_7 || !game->images.img_8 || !game->images.img_9)
    {
        printf("Error: Failed to load digits_images.xpm\n");
        destroy_game(game);
        exit(1);
    }
}

void init_images(t_game *game)
{
    if (!game || !game->mlx)
        return;
    init_map_images(game, 0, 0);
    init_player_images(game);
    init_moves_images(game);
    init_digits_images(game);
}
