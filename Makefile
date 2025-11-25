# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabrgarc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 17:07:05 by gabrgarc          #+#    #+#              #
#    Updated: 2025/11/25 19:26:21 by gabrgarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
FLAGS = -Wall -Wextra -Werror -Ilibft -Iminilibx-linux
COMPILER = cc

SRCS = \
	main.c

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX_DIR     = minilibx-linux/
MLX_LIB     = $(MLX_DIR)libmlx_Linux.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

all: $(MLX_LIB) $(NAME)

$(NAME): $(SRCS) $(LIBFT) $(MLX_LIB)
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR) all

$(LIBFT):
	$(MAKE) -sC $(LIBFT_DIR)

clean:
	$(MAKE) -sC $(LIBFT_DIR) clean
	$(MAKE) -sC $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
