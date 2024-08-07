# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/18 13:04:46 by pmarkaid          #+#    #+#              #
#    Updated: 2024/07/08 12:52:09 by pmarkaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS_FILES = \
	clean_str.c \
	error.c \
	exec_utils.c \
	exec.c \
	main.c \
	parse_args.c \
	pipex.c \
	utils.c \
	free.c

SRC_DIR = src/
SRCS = $(addprefix $(SRC_DIR), $(SRCS_FILES))

BONUS_FILES = \
	clean_str_bonus.c \
	parse_args_bonus.c \
	fd_bonus.c \
	error_bonus.c \
	exec_bonus.c \
	main_bonus.c \
	pipex_bonus.c \
	utils_bonus.c \
	free_bonus.c

SRCS_BONUS = $(addprefix $(SRC_DIR), $(BONUS_FILES))

INCLUDE = -I ./include/

LIBFT_DIR = lib/libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_INCLUDE = -I $(LIBFT_DIR)

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(SRCS_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

all: makelibft $(NAME)

makelibft:
	make -C $(LIBFT_DIR)

bonus: makelibft .bonus

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFT_INCLUDE) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_INCLUDE) $(INCLUDE) $(LIBFT) -o $(NAME)

.bonus: $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT_INCLUDE) $(INCLUDE) $(LIBFT) -o $(NAME)
	touch .bonus

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all makelibft bonus clean fclean re


