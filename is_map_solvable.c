/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_solvable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:52:38 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/30 12:08:30 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

static int	check_collectibles_path(char **map, int player_x, int player_y,
	int map_height)
{
	char	**map_copy;

	map_copy = map_duplicate(map, 0, number_lines(map));
	if (!map_copy)
		return (0);
	find_player_position(map_copy, &player_x, &player_y);
	flood_fill_no_exit(map_copy, player_x, player_y, map_height);
	if (!check_all_collectibles(map_copy))
	{
		free_map(map_copy);
		return (0);
	}
	free_map(map_copy);
	return (1);
}

static int	check_exit_path(char **map, int player_x, int player_y,
		int map_height)
{
	char	**map_copy;

	map_copy = map_duplicate(map, 0, number_lines(map));
	if (!map_copy)
		return (0);
	find_player_position(map_copy, &player_x, &player_y);
	flood_fill(map_copy, player_x, player_y, map_height);
	if (check_exit(map_copy))
	{
		free_map(map_copy);
		return (1);
	}
	free_map(map_copy);
	return (0);
}

int	is_map_solvable(char **map, int player_x, int player_y, int map_height)
{
	int	has_collectibles;

	if (!map)
		return (0);
	has_collectibles = count_collectibles(map);
	find_player_position(map, &player_x, &player_y);
	if (player_x < 0 || player_y < 0)
		return (0);
	if (has_collectibles > 0)
	{
		if (!check_collectibles_path(map, player_x, player_y, map_height))
			return (0);
	}
	return (check_exit_path(map, player_x, player_y, map_height));
}
