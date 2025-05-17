/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_asteroids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:47:26 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/17 14:21:08 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static unsigned int seed;

void	render_asteroids(t_game *game)
{
	t_asteroid *a = game->asteroid;

	while (a)
	{
		mlx_put_image_to_window(game->mlx, game->window,
			game->images.img_asteroid, a->x * TILE_SIZE, a->y * TILE_SIZE);
		a = a->next;
	}
}

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

void	update_asteroids(t_game *game)
{
	static int frame = 0;
	t_asteroid	*curr;
	t_asteroid	*prev;
	t_asteroid	*to_delete;

	frame++;
	if (frame % 10 != 0)
		return ;

	curr = game->asteroid;  // ✅ nom correct
	prev = NULL;
	while (curr)
	{
		curr->x += curr->direction;

		if (curr->x == game->player.x && curr->y == game->player.y)
		{
			printf("💥 Game Over: collision avec astéroïde\n");
			destroy_game(game);
			exit(1);
		}
		if (curr->x < 0 || curr->x >= game->map.map_width)
		{
			to_delete = curr;
			if (prev != NULL)
			{
				prev->next = curr->next;
				curr = prev->next;
			}
			else
			{
				game->asteroid = curr->next;
				curr = game->asteroid;
			}
			free(to_delete);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
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