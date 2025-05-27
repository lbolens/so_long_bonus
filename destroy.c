/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:32:27 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/27 13:42:42 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

static void	destroy_images_map(t_game *game)
{
	if (game->map.map)
		free_map(game->map.map);
	if (game->mlx && game->images.img_floor)
		mlx_destroy_image(game->mlx, game->images.img_floor);
	if (game->mlx && game->images.img_wall)
		mlx_destroy_image(game->mlx, game->images.img_wall);
	if (game->mlx && game->images.img_collectible)
		mlx_destroy_image(game->mlx, game->images.img_collectible);
	if (game->mlx && game->images.img_exit)
		mlx_destroy_image(game->mlx, game->images.img_exit);
	if (game->mlx && game->images.img_asteroid)
		mlx_destroy_image(game->mlx, game->images.img_asteroid);
	if (game->mlx && game->images.img_1x1)
		mlx_destroy_image(game->mlx, game->images.img_1x1);
}

static void	destroy_images_player(t_game *game)
{
	if (game->mlx && game->images.img_player_up)
		mlx_destroy_image(game->mlx, game->images.img_player_up);
	if (game->mlx && game->images.img_player_down)
		mlx_destroy_image(game->mlx, game->images.img_player_down);
	if (game->mlx && game->images.img_player_left)
		mlx_destroy_image(game->mlx, game->images.img_player_left);
	if (game->mlx && game->images.img_player_right)
		mlx_destroy_image(game->mlx, game->images.img_player_right);
}

static void	destroy_moves_images(t_game *game)
{
	if (game->mlx && game->images.img_m)
		mlx_destroy_image(game->mlx, game->images.img_m);
	if (game->mlx && game->images.img_o)
		mlx_destroy_image(game->mlx, game->images.img_o);
	if (game->mlx && game->images.img_v)
		mlx_destroy_image(game->mlx, game->images.img_v);
	if (game->mlx && game->images.img_e)
		mlx_destroy_image(game->mlx, game->images.img_e);
	if (game->mlx && game->images.img_s)
		mlx_destroy_image(game->mlx, game->images.img_s);
	if (game->mlx && game->images.img_points)
		mlx_destroy_image(game->mlx, game->images.img_points);
}

static void	destroy_digits_images(t_game *game)
{
	if (game->mlx && game->images.img_0)
		mlx_destroy_image(game->mlx, game->images.img_0);
	if (game->mlx && game->images.img_1)
		mlx_destroy_image(game->mlx, game->images.img_1);
	if (game->mlx && game->images.img_2)
		mlx_destroy_image(game->mlx, game->images.img_2);
	if (game->mlx && game->images.img_3)
		mlx_destroy_image(game->mlx, game->images.img_3);
	if (game->mlx && game->images.img_4)
		mlx_destroy_image(game->mlx, game->images.img_4);
	if (game->mlx && game->images.img_5)
		mlx_destroy_image(game->mlx, game->images.img_5);
	if (game->mlx && game->images.img_6)
		mlx_destroy_image(game->mlx, game->images.img_6);
	if (game->mlx && game->images.img_7)
		mlx_destroy_image(game->mlx, game->images.img_7);
	if (game->mlx && game->images.img_8)
		mlx_destroy_image(game->mlx, game->images.img_8);
	if (game->mlx && game->images.img_9)
		mlx_destroy_image(game->mlx, game->images.img_9);
}

void	destroy_game(t_game *game)
{
	t_asteroid	*current;
	t_asteroid	*next;

	if (!game)
		return ;
	current = game->asteroid;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	destroy_images_map(game);
	destroy_images_player(game);
	destroy_moves_images(game);
	destroy_digits_images(game);
	if (game->mlx && game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		// Linux
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}
