# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 12:41:12 by ema_blnch         #+#    #+#              #
#    Updated: 2025/04/08 00:42:26 by aelaen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx_macos
INC_DIR = includes
OBJ_DIR = obj
SRC_DIR = srcs

BONUS_DIR = bonus
BONUS_NAME = cub3D_bonus
BONUS_OBJ_DIR = obj_bonus

# BONUS_FILES = $(wildcard $(BONUS_DIR)/*.c)
BONUS_OBJS = $(BONUS_FILES:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

MAKEFLAGS += --no-print-directory

DEF_COLOR	= \033[0;39m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
MAGENTA		= \033[0;95m

SRC_FILES =	error.c \
			main.c \
			validate_file.c \
			check_file_config.c \
			check_map.c \
			check_map_closed.c \
			check_file_utils.c \
			store_data.c \
			parse_textures.c \
			parse_color.c \
			map_utils.c \
			init_window.c \
			minimap.c \
			player.c \
			render.c \
			handle_events.c \
			utils.c \
			raycasting.c \
			raycasting_utils.c

BONUS_FILES = bonus/error.c \
			bonus/main.c \
			bonus/validate_file.c \
			bonus/check_file_config.c \
			bonus/check_map.c \
			bonus/check_map_closed.c \
			bonus/check_file_utils.c \
			bonus/store_data.c \
			bonus/parse_textures.c \
			bonus/parse_color.c \
			bonus/map_utils.c \
			bonus/init_window.c \
			bonus/minimap.c \
			bonus/player.c \
			bonus/render.c \
			bonus/handle_events.c \
			bonus/utils.c \
			bonus/raycasting.c \
			bonus/raycasting_utils.c \
			bonus/sprites.c \
			bonus/doors.c \
			bonus/load_and_set_textures.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


all : $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lm -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(GREEN)cub3D Compiled!$(DEF_COLOR)"


$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)

bonus: $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft -lm -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $(BONUS_NAME)
	@echo "$(GREEN)cub3D Bonus Compiled!$(DEF_COLOR)"

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BONUS_OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	@echo "$(MAGENTA)cub3D objects cleaned !$(DEF_COLOR)"

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make fclean -C $(LIBFT_DIR)
	@echo "$(YELLOW)cub3D cleaned !$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt !$(DEF_COLOR)"


.PHONY: all clean fclean re bonus
