# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 12:28:32 by lbolens           #+#    #+#              #
#    Updated: 2025/05/17 14:17:27 by lbolens          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRC = game.c \
	  get_next_line_utils.c \
	  get_next_line.c \
	  init_images.c \
	  is_map_solvable.c \
	  is_rectangle.c \
	  is_synthax_good.c \
	  is_walls.c \
	  main.c \
	  movements.c \
	  parsing.c \
	  render.c \
	  utils.c \
	  destroy.c \
	  init_asteroids.c

OBJ := $(SRC:%.c=%.o)

CC = gcc
CCFLAGS = -Wall -Wextra -Werror -Imlx -I.

TOTAL := $(words $(SRC))
COUNT = 0

all: $(NAME)

$(NAME): $(OBJ)
	@echo "                                                                                                                                           "
	@echo "         /\    \                 /::\    \                 /\    \   /::\    \                 /\    \                  /\    \            "
	@echo "	/::\    \               /::::\    \               /::\    \ /::::\    \               /::\    \                /::\    \           "
	@echo "       /::::\    \             /::::::\    \             /:::/    //::::::\    \             /::::|   |               /::::\    \           "
	@echo "      /::::::\    \           /::::::::\    \           /:::/    //::::::::\    \           /:::::|   |              /::::::\    \      "
	@echo "     /:::/\:::\    \         /:::/~~\:::\    \         /:::/    //:::/~~\:::\    \         /::::::|   |             /:::/\:::\    \     "
	@echo "    /:::/  \:::\    \       /:::/    \:::\    \       /:::/    //:::/    \:::\    \       /:::/|::|   |            /:::/  \:::\    \    "
	@echo "    \:::\   \:::\    \     /:::/    / \:::\    \     /:::/    //:::/    / \:::\    \     /:::/ |::|   |           /:::/    \:::\    \   "
	@echo "     \:::\   \:::\    \   /:::/    /   \:::\    \   /:::/    //:::/    /   \:::\    \   /:::/  |::|   |          /:::/    / \:::\    \  "
	@echo " /\   \:::\   \:::\    \ |:::|    |     |:::|    | /:::/    /|:::|    |     |:::|    | /:::/   |::|   |/\    \  /:::/    /   \:::\    \ "
	@echo "/::\   \:::\   \:::\____\|:::|    |     |:::|    |/:::/    / |:::|    |     |:::|    |/:: /    |::|   /::\    \/:::/    /     \:::|    |"
	@echo "\:::\   \:::\   \::/    / \:::\    \   /:::/    / \:::\    \  \:::\    \   /:::/    / \::/    /|::|  /:::/    /\:::\    \ /\  /:::|    |"
	@echo " \:::\   \:::\   \/____/   \:::\    \ /:::/    /   \:::\    \  \:::\    \ /:::/    /   \/    / |::| /:::/    /  \:::\    /::\ \::/    / "
	@echo "  \:::\   \:::\    \        \:::\    /:::/    /     \:::\    \  \:::\    /:::/    /            |::|/:::/    /    \:::\   \:::\ \/    /  "
	@echo "   \:::\   \:::\    \        \:::\  /:::/    /       \:::\    \  \:::\  /:::/    /             |::::::/    /      \:::\   \:::\    \    "
	@echo "    \:::\  /:::/    /         \::::::::/    /         \:::\    \  \::::::::/    /              |:::::/    /        \:::\  /:::/    /    "
	@echo "     \:::\/:::/    /           \::::::/    /           \:::\    \  \::::::/    /               |::::/    /          \:::\/:::/    /     "
	@echo "      \::::::/    /             \::::/    /             \:::\    \  \::::/    /                /:::/    /            \::::::/    /      "
	@echo "       \::::/    /               \::/____/               \:::\    \  \::/____/                /:::/    /              \::::/    /       "
	@echo "        \::/    /                                         \::/    /                           \::/    /                \::/____/        "
	@echo "         \/____/                                           \/____/                             \/____/                                  "
                                                                                                                                        
	@make -C mlx --no-print-directory > /dev/null 2>&1
	@echo ""
	# @$(CC) $(CCFLAGS) $^ -Lmlx -lmlx -lXext -lX11 -lm -o $@
	@$(CC) $(CCFLAGS) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@
	@echo "✅ Build complete"

%.o: %.c
	@CURRENT=$$(echo "$(SRC)" | tr ' ' '\n' | nl -v 1 | awk -v f="$<" '$$2==f {print $$1}'); \
	TOTAL=$$(echo "$(SRC)" | wc -w); \
	PERCENT=$$((100 * $$CURRENT / $$TOTAL)); \
	BAR_LEN=20; \
	FILLED=$$((BAR_LEN * $$CURRENT / $$TOTAL)); \
	EMPTY=$$((BAR_LEN - $$FILLED)); \
	BAR=$$(printf "%*s" $$FILLED | tr ' ' '#'); \
	SPACE=$$(printf "%*s" $$EMPTY); \
	printf "\r[%s%s] %3d%% Compiling: %-20s" "$$BAR" "$$SPACE" "$$PERCENT" "$<"; \
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "🧹 Cleaned object files"

fclean: clean
	@make clean -C mlx > /dev/null
	@rm -f $(NAME)
	@echo "🧹 Fully cleaned project"

re: fclean all
