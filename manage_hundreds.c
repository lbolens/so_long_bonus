/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_hundreds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:14:32 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/27 15:52:03 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

static void	reduce_function(t_game *game, char *moves, int i, int j)
{
	if (moves[0] == '5')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_5, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[0] == '6')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_6, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[0] == '7')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_7, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[0] == '8')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_8, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[0] == '9')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_9, j
			* TILE_SIZE, i * TILE_SIZE);
}

void	manage_hundreds_for_hundreds(t_game *game, char *moves, int i, int j)
{
	if (moves[0] == '0')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_0, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[0] == '1')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_1, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[0] == '2')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_2, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[0] == '3')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_3, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[0] == '4')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_4, j
			* TILE_SIZE, i * TILE_SIZE);
	reduce_function(game, moves, i, j);
}

static void	reduce_function_bis(t_game *game, char *moves, int i, int j)
{
	if (moves[1] == '5')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_5, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[1] == '6')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_6, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[1] == '7')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_7, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[1] == '8')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_8, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[1] == '9')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_9, j
			* TILE_SIZE, i * TILE_SIZE);
}

void	manage_tens_for_hundreds(t_game *game, char *moves, int i, int j)
{
	if (moves[1] == '0')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_0, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[1] == '1')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_1, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[1] == '2')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_2, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[1] == '3')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_3, j
			* TILE_SIZE, i * TILE_SIZE);
	else if (moves[1] == '4')
		mlx_put_image_to_window(game->mlx, game->window, game->images.img_4, j
			* TILE_SIZE, i * TILE_SIZE);
	reduce_function_bis(game, moves, i, j);
}
