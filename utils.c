/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:06:34 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/27 16:08:54 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

int	number_lines(char **map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	number_columns(char *map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i] && map[i] != '\n')
		i++;
	return (i);
}

int	number_collectibles(char **map)
{
	int	i;
	int	j;
	int	nbr_c;

	if (!map)
		return (0);
	i = 0;
	nbr_c = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				nbr_c++;
			j++;
		}
		i++;
	}
	return (nbr_c);
}

int	check_file_synthax(char *str)
{
	int	len;

	if (!str)
		return (1);
	len = 0;
	while (str[len])
		len++;
	if (len < 5)
		return (1);
	if (str[len - 4] == '.' && str[len - 3] == 'b' && str[len - 2] == 'e'
		&& str[len - 1] == 'r')
		return (0);
	return (1);
}

int	close_game(t_game *game)
{
	if (game)
		destroy_game(game);
	exit(0);
}
