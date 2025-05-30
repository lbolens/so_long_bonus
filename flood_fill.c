/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:57:24 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/30 12:07:49 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

static int	is_boundary_or_obstacle_no_exit(char **map, int x, int y,
		int map_height)
{
	if (x < 0 || y < 0 || y >= map_height || !map[y] || !map[y][x])
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'V'
		|| map[y][x] == 'E')
		return (1);
	return (0);
}

static int	is_valid_cell_no_exit(char c)
{
	return (c == '0' || c == 'C' || c == 'P');
}

void	flood_fill(char **map, int x, int y, int map_height)
{
	if (is_boundary_or_obstacle(map, x, y, map_height))
		return ;
	if (is_valid_cell(map[y][x]))
		map[y][x] = 'V';
	flood_fill(map, x + 1, y, map_height);
	flood_fill(map, x - 1, y, map_height);
	flood_fill(map, x, y + 1, map_height);
	flood_fill(map, x, y - 1, map_height);
}

void	flood_fill_no_exit(char **map, int x, int y, int map_height)
{
	if (is_boundary_or_obstacle_no_exit(map, x, y, map_height))
		return ;
	if (is_valid_cell_no_exit(map[y][x]))
		map[y][x] = 'V';
	flood_fill_no_exit(map, x + 1, y, map_height);
	flood_fill_no_exit(map, x - 1, y, map_height);
	flood_fill_no_exit(map, x, y + 1, map_height);
	flood_fill_no_exit(map, x, y - 1, map_height);
}
