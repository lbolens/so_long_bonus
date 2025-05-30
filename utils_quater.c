/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quater.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:57 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/28 14:21:51 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

void	init_seed_from_map(t_game *game)
{
	game->seed = game->map.map[0][0] * 31 + game->player.x * 7 + game->player.y
		* 9;
}

int	my_rand_mod(t_game *game, int mod)
{
	game->seed = game->seed * 1103515245 + 12345;
	return ((game->seed / 65536) % mod);
}

void	render_map(t_game *game, int i, int j)
{
	char	**map;

	map = game->map.map;
	doing_render(game, map, i, j);
}

void	init_digit_images_bis(t_game *game)
{
	int	w;
	int	h;

	w = TILE_SIZE;
	h = TILE_SIZE;
	game->images.img_5 = NULL;
	game->images.img_6 = NULL;
	game->images.img_7 = NULL;
	game->images.img_8 = NULL;
	game->images.img_9 = NULL;
	game->images.img_5 = mlx_xpm_file_to_image(game->mlx, "textures/img_5.xpm",
			&w, &h);
	game->images.img_6 = mlx_xpm_file_to_image(game->mlx, "textures/img_6.xpm",
			&w, &h);
	game->images.img_7 = mlx_xpm_file_to_image(game->mlx, "textures/img_7.xpm",
			&w, &h);
	game->images.img_8 = mlx_xpm_file_to_image(game->mlx, "textures/img_8.xpm",
			&w, &h);
	game->images.img_9 = mlx_xpm_file_to_image(game->mlx, "textures/img_9.xpm",
			&w, &h);
}

void	check_images(t_game *game)
{
	if (!game->images.img_0 || !game->images.img_1 || !game->images.img_1x1
		|| !game->images.img_2 || !game->images.img_3 || !game->images.img_4
		|| !game->images.img_5 || !game->images.img_6 || !game->images.img_7
		|| !game->images.img_8 || !game->images.img_9
		|| !game->images.img_asteroid || !game->images.img_collectible
		|| !game->images.img_e || !game->images.img_exit
		|| !game->images.img_floor || !game->images.img_m || !game->images.img_o
		|| !game->images.img_player_down || !game->images.img_player_left
		|| !game->images.img_player_right || !game->images.img_player_up
		|| !game->images.img_points || !game->images.img_s
		|| !game->images.img_v || !game->images.img_wall)
	{
		printf("Error\nFailed to load an image\n");
		destroy_game(game);
		exit(1);
	}
}
