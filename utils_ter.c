/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:55 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/27 16:09:56 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

static char	*ft_putnbr(int n, char *s, int size, int *i)
{
	long	a;

	a = n;
	if (a < 0)
	{
		s[*i] = '-';
		(*i)++;
		a *= -1;
	}
	if (a >= 10)
		ft_putnbr(a / 10, s, size, i);
	s[*i] = (a % 10) + '0';
	(*i)++;
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		size;
	int		i;

	size = ft_size(n);
	s = (char *)malloc((size + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	s = ft_putnbr(n, s, size, &i);
	s[size] = '\0';
	return (s);
}

int	exit_y(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->map.map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

int	exit_x(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->map.map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				return (j);
			j++;
		}
		i++;
	}
	return (0);
}
