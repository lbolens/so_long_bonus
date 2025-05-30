/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_solvable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:52:38 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/30 12:13:33 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static char	**map_duplicate(char **map, int i, int j, int nbr_lines)
{
	char	**map_duplicate;
	int		len;

	map_duplicate = (char **)malloc((nbr_lines + 1) * sizeof(char *));
	if (!map_duplicate)
		return (NULL);
	while (map[i])
	{
		j = 0;
		len = number_columns(map[i]);
		map_duplicate[i] = malloc((len + 1) * sizeof(char));
		if (!map_duplicate[i])
		{
			while (--i >= 0)
				free(map_duplicate[i]);
			free(map_duplicate);
			return (NULL);
		}
		while (j < len)
		{
			map_duplicate[i][j] = map[i][j];
			j++;
		}
		map_duplicate[i][j] = '\0';
		i++;
	}
	map_duplicate[i] = NULL;
	return (map_duplicate);
}

static void	flood_fill(char **map, int x, int y, int map_height)
{
	if (x < 0 || y < 0 || y >= map_height || !map[y] || !map[y][x])
		return ;
	if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'V')
		return ;
	if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'E'
		|| map[y][x] == 'P')
		map[y][x] = 'V';
	flood_fill(map, x + 1, y, map_height);
	flood_fill(map, x - 1, y, map_height);
	flood_fill(map, x, y + 1, map_height);
	flood_fill(map, x, y - 1, map_height);
}

static void	flood_fill_no_exit(char **map, int x, int y, int map_height)
{
	if (x < 0 || y < 0 || y >= map_height || !map[y] || !map[y][x])
		return ;
	if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'V'
		|| map[y][x] == 'E')
		return ;
	if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'P')
		map[y][x] = 'V';
	flood_fill_no_exit(map, x + 1, y, map_height);
	flood_fill_no_exit(map, x - 1, y, map_height);
	flood_fill_no_exit(map, x, y + 1, map_height);
	flood_fill_no_exit(map, x, y - 1, map_height);
}

int	is_map_solvable(char **map, int player_x, int player_y, int map_height)
{
	char	**map_copy;
	int		has_collectibles;

	if (!map)
		return (0);
	has_collectibles = count_collectibles(map);
	map_copy = map_duplicate(map, 0, 0, number_lines(map));
	if (!map_copy)
		return (0);
	find_player_position(map_copy, &player_x, &player_y);
	if (player_x >= 0 && player_y >= 0)
	{
		if (has_collectibles > 0)
		{
			flood_fill_no_exit(map_copy, player_x, player_y, map_height);
			if (!check_all_collectibles(map_copy))
			{
				free_map(map_copy);
				return (0);
			}
			free_map(map_copy);
			map_copy = map_duplicate(map, 0, 0, number_lines(map));
			if (!map_copy)
				return (0);
			find_player_position(map_copy, &player_x, &player_y);
		}
		flood_fill(map_copy, player_x, player_y, map_height);
		if (check_exit(map_copy))
		{
			free_map(map_copy);
			return (1);
		}
	}
	free_map(map_copy);
	return (0);
}
