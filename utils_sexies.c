/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sexies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:55:22 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/30 12:05:55 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

char	*duplicate_line(char *line)
{
	int		len;
	char	*new_line;
	int		j;

	len = number_columns(line);
	new_line = malloc((len + 1) * sizeof(char));
	j = 0;
	if (!new_line)
		return (NULL);
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

	map_duplicate = (char **)malloc((nbr_lines + 1) * sizeof(char *));
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

int	is_boundary_or_obstacle(char **map, int x, int y, int map_height)
{
	if (x < 0 || y < 0 || y >= map_height || !map[y] || !map[y][x])
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'V')
		return (1);
	return (0);
}

int	is_valid_cell(char c)
{
	return (c == '0' || c == 'C' || c == 'E' || c == 'P');
}
