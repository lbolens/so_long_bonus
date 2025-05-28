/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quinter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:50:24 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/28 11:56:03 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

int	check_all_collectibles(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_exit(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	count_collectibles(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	validate_size(char **map)
{
	int	cols;
	int	rows;
	int	w;
	int	h;

	cols = number_columns(map[0]);
	rows = number_lines(map);
	w = cols * TILE_SIZE;
	h = rows * TILE_SIZE;
	return (w <= MAX_WIDTH && h <= MAX_HEIGHT);
}

int	validate_content(char **map, int p, int e, int c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (((i == 0 || !map[i + 1]) || (j == 0 || !map[i][j + 1]))
				&& map[i][j] != '1')
				return (0);
			if (map[i][j] == 'P')
				p++;
			else if (map[i][j] == 'E')
				e++;
			else if (map[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	return (p == 1 && e >= 1 && c >= 1);
}
