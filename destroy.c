/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:32:27 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/17 14:33:36 by lbolens          ###   ########.fr       */
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
void	destroy_game(t_game *game)
{
	t_asteroid *current;
	t_asteroid *next;

	if (!game)
		return ;
		
	// Libération de la liste d'astéroïdes
	current = game->asteroid;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	
	destroy_images_map(game);
	destroy_images_player(game);
	if (game->mlx && game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		//Linux
		//mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}