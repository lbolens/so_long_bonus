/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:06:34 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/26 11:36:01 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

static unsigned int seed;

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

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	find_player_position(char **map, int *player_x, int *player_y)
{
	int	i;
	int	j;

	if (!map || !player_x || !player_y)
		return ;
	*player_x = -1;
	*player_y = -1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*player_x = j;
				*player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen_2(s1) + ft_strlen_2(s2);
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen_2(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

static int	ft_size(int num)
{
	int		size;
	long	n;

	n = num;
	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n >= 10)
	{
		n = n / 10;
		size++;
	}
	size++;
	return (size);
}

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
	char** map;
	int	i;
	int	j;

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
	char** map;
	int	i;
	int	j;

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

void init_seed_from_map(t_game *game)
{
	seed = game->map.map[0][0] * 31
	      + game->player.x * 17
	      + game->player.y * 13;
}

int my_rand_mod(int mod)
{
	seed = seed * 1103515245 + 12345;
	return (seed / 65536) % mod;
}
