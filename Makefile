# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguardam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 12:00:00 by gguardam          #+#    #+#              #
#    Updated: 2025/06/06 12:00:00 by gguardam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCE = 	main.c \
			parser.c \
			math_utils.c \
			render.c \
			events.c \
			fractol_utils/parser_utils.c \
			init.c
OBJ = $(SOURCE:.c=.o)
INCLUDE = fractol.h
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = ./printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
LIBS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf -lXext -lX11 -lm
INCLUDES = -I. -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(MLX_DIR)
RM = rm -f

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(MLX) $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus