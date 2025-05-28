/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sexies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:49:18 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/28 11:53:48 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

char	**allocate_map_memory(int nbr_lines)
{
	char	**map_duplicate;

	map_duplicate = (char **)malloc((nbr_lines + 1) * sizeof(char *));
	return (map_duplicate);
}

char	*duplicate_line(char *line)
{
	char	*new_line;
	int		len;
	int		j;

	len = number_columns(line);
	new_line = malloc((len + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	j = 0;
	while (j < len)
	{
		new_line[j] = line[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

void	free_partial_map(char **map, int up_to_index)
{
	while (--up_to_index >= 0)
		free(map[up_to_index]);
	free(map);
}

char	**map_duplicate(char **map, int i, int nbr_lines)
{
	char	**map_duplicate;

	map_duplicate = allocate_map_memory(nbr_lines);
	if (!map_duplicate)
		return (NULL);
	while (map[i])
	{
		map_duplicate[i] = duplicate_line(map[i]);
		if (!map_duplicate[i])
		{
			free_partial_map(map_duplicate, i);
			return (NULL);
		}
		i++;
	}
	map_duplicate[i] = NULL;
	return (map_duplicate);
}

void	flood_fill(char **map, int x, int y, int map_height)
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
