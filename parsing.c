/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:23:29 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/28 12:02:03 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

static void	strip_newline(char *line)
{
	int	len;

	len = ft_strlen_2(line);
	while (len && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[--len] = '\0';
}

static int	open_map_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("open_map_file");
	return (fd);
}

static char	**load_map(int fd)
{
	char	**map;
	char	*line;
	size_t	count;

	map = malloc(sizeof * map * (MAX_LINES + 1));
	if (!map)
		return (NULL);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		map[count++] = line;
		if (count >= MAX_LINES)
			break ;
		line = get_next_line(fd);
	}
	map[count] = NULL;
	return (map);
}

static int	validate_shape(char **map)
{
	size_t	i;
	size_t	len0;

	if (!map || !map[0])
		return (0);
	len0 = ft_strlen_2(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen_2(map[i]) != len0)
			return (0);
		i++;
	}
	return (1);
}

char	**is_map_valid(char *filepath)
{
	int		fd;
	char	**map;

	fd = open_map_file(filepath);
	if (fd < 0)
		return (NULL);
	map = load_map(fd);
	close(fd);
	if (!map)
		return (NULL);
	if (!validate_shape(map) || !validate_content(map, 0, 0, 0)
		|| !validate_size(map))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
