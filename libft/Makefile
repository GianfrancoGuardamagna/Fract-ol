# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguardam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 16:26:25 by gguardam          #+#    #+#              #
#    Updated: 2025/05/12 15:21:14 by gguardam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCE = ft_atoi.c \
         ft_isalpha.c \
         ft_memchr.c \
         ft_memset.c \
         ft_strlcpy.c \
         ft_strrchr.c \
         ft_bzero.c \
         ft_isdigit.c \
         ft_memcmp.c \
         ft_strchr.c \
         ft_strlen.c \
         ft_tolower.c \
         ft_calloc.c \
         ft_isprint.c \
	 ft_isascii.c \
         ft_memcpy.c \
         ft_strdup.c \
         ft_strncmp.c \
         ft_itoa.c \
         ft_putchar_fd.c \
         ft_putendl_fd.c \
         ft_putnbr_fd.c \
         ft_putstr_fd.c \
         ft_split.c \
         ft_striteri.c \
         ft_strjoin.c \
         ft_strmapi.c \
         ft_strtrim.c \
         ft_substr.c \
         ft_toupper.c \
         ft_isalnum.c \
         ft_memmove.c \
         ft_strlcat.c \
         ft_atof.c \
         ft_strnstr.c

OBJ = $(SOURCE:.c=.o)

INCLUDE = libft.h

AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
