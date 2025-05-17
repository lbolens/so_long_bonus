/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_asteroids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:47:26 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/17 13:54:51 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static unsigned int seed;

void init_seed_from_map(t_game *game)
{
	seed = game->map.map[0][0] * 31
	      + game->player.x * 17
	      + game->player.y * 13;
}

int my_rand_mod(int mod)
{
	seed = seed * 1103515245 + 12345;
	return (seed / 65536) % mod;
}

void init_asteroid(t_game *game)
{
	t_asteroid *a = malloc(sizeof(t_asteroid));
	if (!a)
		return ;

	int dy = my_rand_mod(3) - 1; // -1, 0 ou +1
	int y = game->player.y + dy;

	if (y < 1 || y >= game->map.map_height - 1)
		y = game->player.y; // limite aux bords

	a->y = y;
	a->x = 0;
	a->direction = 1;

	a->next = game->asteroid;
	game->asteroid = a;
}