/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:53:40 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/27 15:31:34 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

static void	manage_keycode(t_game *game, int keycode, int *new_x, int *new_y)
{
	if (!game || !new_x || !new_y)
		return ;
	*new_x = game->player.x;
	*new_y = game->player.y;
	if (keycode == KEY_W || keycode == KEY_UP)
		*new_y -= 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		*new_y += 1;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		*new_x -= 1;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		*new_x += 1;
	else if (keycode == KEY_ESC)
	{
		destroy_game(game);
		exit(0);
	}
}

static int	manage_conditions(t_game *game, char **map, int new_x, int new_y)
{
	char	next_tile;

	if (!game || !map || new_x < 0 || new_y < 0 || !map[new_y])
		return (0);
	next_tile = map[new_y][new_x];
	if (next_tile == '1')
		return (0);
	if (next_tile == 'C')
	{
		game->player.collected++;
		map[new_y][new_x] = '0';
	}
	if (next_tile == 'E')
	{
		if (game->player.collected == game->map.total_collectibles)
		{
			printf("Victory!\n");
			destroy_game(game);
			exit(0);
		}
		return (0);
	}
	return (1);
}

int	key_handler(int keycode, t_game *game)
{
	char	**map;
	int		new_x;
	int		new_y;

	if (!game || !game->map.map)
		return (0);
	map = game->map.map;
	new_x = game->player.x;
	new_y = game->player.y;
	manage_keycode(game, keycode, &new_x, &new_y);
	if (new_y < 0 || new_x < 0 || !map[new_y] || !map[new_y][new_x])
		return (0);
	if (manage_conditions(game, map, new_x, new_y) == 0)
		return (0);
	map[game->player.y][game->player.x] = '0';
	game->player.last_x = game->player.x;
	game->player.last_y = game->player.y;
	game->player.x = new_x;
	game->player.y = new_y;
	map[new_y][new_x] = 'P';
	game->player.moves++;
	printf("Moves: %d\n", game->player.moves);
	return (0);
}
