/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:23:29 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/15 15:47:05 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

char** is_map_valid(char *filepath, int fd, int i)
{
    char    **map;
    int     screen_width;
    int     screen_height;

    if (!filepath)
        return (NULL);
    fd = open(filepath, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Cannot open file\n");
        return (NULL);
    }
    map = (char **)malloc(1024 * sizeof(char *));
    if (!map)
    {
        close(fd);
        return (NULL);
    }
    while ((map[i] = get_next_line(fd)) != NULL)
        i++;
    if (i == 0)
    {
        free(map);
        close(fd);
        printf("Error: Empty map\n");
        return (NULL);
    }   
    map[i] = NULL;
    close(fd);
    if (is_rectangle(map) == 0 || check_synthax(map, 0, 0, 0) == 0 || (is_walls(map, 0, number_lines(map), number_columns(map[0])) == 0) || is_map_solvable(map) == 0)
    {
        free_map(map);
        return (NULL);
    }
    screen_width = 3840;
    screen_height = 2160;
    if (number_columns(map[0]) * TILE_SIZE > screen_width ||
        number_lines(map) * TILE_SIZE > screen_height)
    {
        printf("Error: map exceeds screen size\n");
        free_map(map);
        return NULL;
    }
    return (map);
}
