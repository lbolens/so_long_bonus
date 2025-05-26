/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:02:54 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/26 11:33:43 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"


void    doing_it(t_game *game, int* width_px, int* heigth_px)
{
    if (!game || !game->map.map || !width_px || !heigth_px)
    {
        printf("Error: Invalid pointers in doing_it\n");
        exit(1);
    }    
    *width_px = number_columns(game->map.map[0]) * TILE_SIZE;
    *heigth_px = number_lines(game->map.map) * TILE_SIZE;
    init_game(game, game->map.map);
    game->window = mlx_new_window(game->mlx, *width_px, *heigth_px, "so_long");
    if (!game->window)
    {
        destroy_game(game);
        exit(1);
    }
    render_map(game, 0, 0);
    mlx_key_hook(game->window, key_handler, game);
    mlx_hook(game->window, 17, 0, close_game, game);
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
    destroy_game(game);
}

int main(int argc, char **argv)
{
    t_game *game;
    int width_px;
    int height_px;
    
    if (argc != 2 || check_file_synthax(argv[1]) == 1)
    {
        printf("Error: invalid file\n");
        return (1);
    }    
    game = malloc(sizeof(t_game));
    if (!game)
    {
        printf("Error: Failed to allocate memory for game structure\n");
        return (1);
    }
    game->mlx = NULL;
    game->window = NULL;
    game->asteroid = NULL;
    game->map.map = NULL;    
    game->map.map = is_map_valid(argv[1], 0, 0);
    if (!game->map.map)
    {
        printf("Error: invalid map\n");
        free(game);
        return (1);
    }
    width_px = 0;
    height_px = 0;
    doing_it(game, &width_px, &height_px);
    return (0);
}

