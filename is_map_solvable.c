/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_solvable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:52:38 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/15 15:23:21 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static char    **map_duplicate(char **map, int i, int j, int nbr_lines)
{
    char** map_duplicate;
    int len;

    map_duplicate = (char**)malloc((nbr_lines + 1) * sizeof(char*));
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

// Flood fill standard - marque toutes les cases accessibles avec 'V'
static void    flood_fill(char** map, int x, int y, int map_height)
{
    if (x < 0 || y < 0 || y >= map_height || !map[y] || !map[y][x])
        return;
        
    if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'V')
        return;
        
    if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'E' || map[y][x] == 'P')
        map[y][x] = 'V';
        
    flood_fill(map, x + 1, y, map_height);
    flood_fill(map, x - 1, y, map_height);
    flood_fill(map, x, y + 1, map_height);
    flood_fill(map, x, y - 1, map_height);
}

// Flood fill qui ne peut pas traverser les sorties (E)
static void    flood_fill_no_exit(char** map, int x, int y, int map_height)
{
    if (x < 0 || y < 0 || y >= map_height || !map[y] || !map[y][x])
        return;
        
    // On ne peut pas traverser les murs, cases déjà visitées ou sorties
    if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'V' || map[y][x] == 'E')
        return;
        
    // Marquer la case comme visitée
    if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'P')
        map[y][x] = 'V';
        
    // Explorer dans les 4 directions
    flood_fill_no_exit(map, x + 1, y, map_height);
    flood_fill_no_exit(map, x - 1, y, map_height);
    flood_fill_no_exit(map, x, y + 1, map_height);
    flood_fill_no_exit(map, x, y - 1, map_height);
}

// Vérifie si tous les collectibles sont accessibles
static int check_all_collectibles(char** map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'C')
                return (0);  // Il reste des collectibles non accessibles
            j++;
        }
        i++;
    }
    return (1);  // Tous les collectibles sont accessibles
}

// Vérifie si la sortie est accessible
static int check_exit(char** map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'E')
                return (0);  // La sortie n'est pas accessible
            j++;
        }
        i++;
    }
    return (1);  // La sortie est accessible
}

// Compte le nombre de collectibles sur la carte
static int count_collectibles(char** map)
{
    int i;
    int j;
    int count;

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

int is_map_solvable(char** map)
{
    char** map_copy;
    int player_x;
    int player_y;
    int map_height;
    int has_collectibles;

    if (!map)
        return (0);
        
    // Vérifier s'il y a des collectibles sur la carte
    has_collectibles = count_collectibles(map);
    
    map_copy = map_duplicate(map, 0, 0, number_lines(map));
    if (!map_copy)
        return (0);
        
    map_height = number_lines(map_copy);
    player_x = -1;
    player_y = -1;
    find_player_position(map_copy, &player_x, &player_y);
    
    if (player_x >= 0 && player_y >= 0)
    {
        // Première vérification: le joueur peut-il atteindre tous les collectibles
        // SANS passer par la sortie ?
        if (has_collectibles > 0)
        {
            // On fait un flood_fill qui ne passe pas par la sortie
            flood_fill_no_exit(map_copy, player_x, player_y, map_height);
            
            // On vérifie si tous les collectibles sont accessibles
            if (!check_all_collectibles(map_copy))
            {
                // Certains collectibles ne sont pas accessibles sans passer par la sortie
                free_map(map_copy);
                return (0);
            }
            
            // On réinitialise map_copy pour la deuxième vérification
            free_map(map_copy);
            map_copy = map_duplicate(map, 0, 0, number_lines(map));
            if (!map_copy)
                return (0);
                
            find_player_position(map_copy, &player_x, &player_y);
        }
        
        // Deuxième vérification: le joueur peut-il atteindre la sortie après avoir collecté tous les collectibles?
        flood_fill(map_copy, player_x, player_y, map_height);
        
        // Vérifier si la sortie est accessible
        if (check_exit(map_copy))
        {
            free_map(map_copy);
            return (1);  // La carte est solvable
        }
    }
    
    free_map(map_copy);
    return (0);  // Par défaut, la carte n'est pas solvable
}
