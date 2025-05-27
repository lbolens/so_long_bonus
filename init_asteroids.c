/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_asteroids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:47:26 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/27 16:47:05 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

void	render_asteroids(t_game *game)
{
	t_asteroid	*a;
	char		**map;

	a = game->asteroid;
	map = game->map.map;
	while (a)
	{
		if (map[a->y][a->x] != '1' && map[a->y][a->x] != 'C'
			&& map[a->y][a->x] != 'E')
			mlx_put_image_to_window(game->mlx, game->window,
				game->images.img_asteroid, a->x * TILE_SIZE, a->y * TILE_SIZE);
		a = a->next;
	}
}

static void	reduce_function_bis(t_game *game, t_asteroid *curr,
		t_asteroid **prev)
{
	t_asteroid	*to_delete;

	to_delete = curr;
	if (*prev != NULL)
	{
		(*prev)->next = curr->next;
		curr = (*prev)->next;
	}
	else
	{
		game->asteroid = curr->next;
		curr = game->asteroid;
	}
	free(to_delete);
}

static void	reduce_function(t_game *game)
{
	printf("💥 Game Over: collision avec astéroïde\n");
	destroy_game(game);
	exit(1);
}

void	update_asteroids(t_game *game, t_asteroid *curr, t_asteroid *prev)
{
	static int	frame = 0;
	t_asteroid	*next;

	frame++;
	if (frame % 15 != 0)
		return ;
	curr = game->asteroid;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->x += curr->direction;
		if (curr->x == exit_x(game) && curr->y == exit_y(game))
			curr->x = curr->x + 1;
		if ((curr->x == game->player.x && curr->y == game->player.y) || (curr->x
				- 1 == game->player.x && curr->y == game->player.y))
			reduce_function(game);
		if (curr->x < 0 || curr->x >= game->map.map_width - 1)
			reduce_function_bis(game, curr, &prev);
		else
		{
			prev = curr;
		}
		curr = next;
	}
}

void	init_asteroid(t_game *game)
{
	t_asteroid	*a;
	int			dy;
	int			y;

	a = malloc(sizeof(t_asteroid));
	if (!a)
		return ;
	dy = my_rand_mod(3) - 1;
	y = game->player.y + dy;
	if (y < 1 || y >= game->map.map_height - 1)
		y = game->player.y;
	a->y = y;
	a->x = 0;
	a->direction = 1;
	a->next = game->asteroid;
	game->asteroid = a;
}
