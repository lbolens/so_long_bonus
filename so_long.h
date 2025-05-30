/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:49:58 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/30 12:00:32 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 128
# endif

/* Sur Linux*/
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/*Sur Mac
# define KEY_W     13
# define KEY_A     0
# define KEY_S     1
# define KEY_D     2
# define KEY_ESC   53
# define KEY_ENTER 36
# define KEY_UP    126
# define KEY_DOWN  125
# define KEY_LEFT  123
# define KEY_RIGHT 124
# define KEY_SPACE 49
*/

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char				*content;
	struct s_node		*next;
}						t_nod;

typedef struct s_images
{
	void				*img_1x1;
	void				*img_wall;
	void				*img_player_up;
	void				*img_player_down;
	void				*img_player_left;
	void				*img_player_right;
	void				*img_collectible;
	void				*img_exit;
	void				*img_floor;
	void				*img_asteroid;
	void				*img_victory;
	void				*img_game_over;
	void				*img_m;
	void				*img_o;
	void				*img_v;
	void				*img_e;
	void				*img_s;
	void				*img_points;
	void				*img_0;
	void				*img_1;
	void				*img_2;
	void				*img_3;
	void				*img_4;
	void				*img_5;
	void				*img_6;
	void				*img_7;
	void				*img_8;
	void				*img_9;
}						t_images;

typedef struct s_player
{
	int					x;
	int					y;
	int					last_x;
	int					last_y;
	int					moves;
	int					collected;
}						t_player;

typedef struct s_map
{
	char				**map;
	int					map_width;
	int					map_height;
	int					total_collectibles;
}						t_map;

typedef struct s_asteroid
{
	int					x;
	int					y;
	int					direction;
	unsigned int		seed;
	struct s_asteroid	*next;
}						t_asteroid;

typedef struct s_game
{
	void				*mlx;
	void				*window;
	unsigned int		seed;
	t_images			images;
	t_map				map;
	t_player			player;
	t_asteroid			*asteroid;
}						t_game;

/*--------GET_NEXT_LINE--------*/
char					*get_next_line(int fd);
int						check_newline(char *str);
char					*ft_split_the_stash(t_nod *stash, int i, int j,
							int size);
void					ft_clean_stash(t_nod **stash);
void					free_stash(t_nod **stash);
int						ft_strlen_str(const char *s);
t_nod					*ft_create_new_stash(char *content, int index);
t_nod					*add_to_stash(t_nod *stash, char *buffer);

/*--------PARSING--------*/
int						is_map_solvable(char **map, int player_x, int player_y,
							int map_height);
int						is_rectangle(char **map);
int						check_synthax(char **map, int nbr_p, int nbr_c,
							int nbr_e);
int						is_walls(char **map, int i, int nbr_lines,
							int nbr_columns);
char					**is_map_valid(char *filepath, int fd, int i);

/*--------DOING_IT--------*/
void					init_game(t_game *game, char **map);
void					init_images(t_game *game);
int						key_handler(int keycode, t_game *game);
void					render_map(t_game *game, int i, int j);

/*--------UTILS--------*/
int						number_lines(char **map);
int						number_columns(char *map);
int						number_collectibles(char **map);
int						check_file_synthax(char *str);
int						close_game(t_game *game);
void					free_map(char **map);
void					destroy_game(t_game *game);
void					find_player_position(char **map, int *player_x,
							int *player_y);

char					*ft_itoa(int n);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlen_2(const char *str);

int						game_loop(t_game *game);
void					render_asteroids(t_game *game);
void					init_seed_from_map(t_game *game);
int						my_rand_mod(t_game *game, int mod);
void					update_asteroids(t_game *game, t_asteroid *curr,
							t_asteroid *prev);
void					init_asteroid(t_game *game);
int						exit_x(t_game *game);
int						exit_y(t_game *game);

void					doing_it(t_game *game, int *width_px, int *heigth_px);
int						manage_victory_and_game_over(int keycode, t_game *game);

void					manage_units_for_units(t_game *game, char *moves, int i,
							int j);
void					manage_hundreds_for_hundreds(t_game *game, char *moves,
							int i, int j);
void					manage_tens_for_hundreds(t_game *game, char *moves,
							int i, int j);
void					manage_units_for_hundreds(t_game *game, char *moves,
							int i, int j);
void					manage_tens_for_tens(t_game *game, char *moves, int i,
							int j);
void					manage_units_for_tens(t_game *game, char *moves, int i,
							int j);
void					doing_render(t_game *game, char **map, int i, int j);
int						ft_size(int num);
void					init_digit_images_bis(t_game *game);
int						check_all_collectibles(char **map);
int						check_exit(char **map);
int						count_collectibles(char **map);

char *duplicate_line(char *line);
void free_partial_map(char **map, int up_to_index);
char **map_duplicate(char **map, int i, int nbr_lines);
int is_boundary_or_obstacle(char **map, int x, int y, int map_height);
int is_valid_cell(char c);

void flood_fill(char **map, int x, int y, int map_height);
void flood_fill_no_exit(char **map, int x, int y, int map_height);

#endif