/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:02:54 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/17 14:05:35 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"


static void    doing_it(t_game *game, int* width_px, int* heigth_px)
{
    *width_px = number_columns(game->map.map[0]) * TILE_SIZE;
    *heigth_px = number_lines(game->map.map) * TILE_SIZE;
    init_game(game, game->map.map);
    game->window = mlx_new_window(game->mlx, *width_px, *heigth_px, "so_long");
    if (!game->window)
    {
        printf("Error: Failed to create window\n");
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
        printf("Error : invalid file\n");
        return (1);
    }
    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    game->map.map = is_map_valid(argv[1], 0, 0);
    if (!game->map.map)
    {
        printf("Error : invalid map\n");
        free(game);
        return (1);
    }
    width_px = 0;
    height_px = 0;
    doing_it(game, &width_px, &height_px);
    return (0);
}
