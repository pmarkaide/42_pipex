# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/18 13:04:46 by pmarkaid          #+#    #+#              #
#    Updated: 2024/02/18 13:08:37 by pmarkaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = \
	main.c

SRCS_DIR = src
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

LIB_DIR = lib

LIBFT_REPO = https://github.com/pmarkaide/42_libft
LIBFT_TAG = v.1.2.0
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJS = $(SRCS:.c=.o)

LIBFT_INCLUDE = -I $(LIBFT_DIR)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

$(LIBFT):
	git clone --branch $(LIBFT_TAG) --single-branch $(LIBFT_REPO) $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFT_INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT_INCLUDE) -o $(NAME) $(OBJS) $(LIBFT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
