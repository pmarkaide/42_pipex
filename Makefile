# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/18 13:04:46 by pmarkaid          #+#    #+#              #
#    Updated: 2024/02/18 15:55:21 by pmarkaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = \
	main.c \
	error.c \
	utils.c

SRCS_DIR = src

LIB_DIR = lib

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJS = $(SRCS:.c=.o)

LIBFT_INCLUDE = -I $(LIBFT_DIR)
LIBFT_MARKER = .libft

CC = gcc
CFLAGS = -Wall -Wextra

all: makelibft $(NAME)

# Make libft
makelibft:
	make -C $(LIBFT_DIR)

# Create marker if libft.a in libft directory changed (makelibft had run)
$(LIBFT_MARKER): $(LIBFT)
	touch $(LIBFT_MARKER)

# Copy libft only if marker changed (makelibft had run and changed the marker)
$(LIBFT): $(LIBFT_MARKER)
	cp $(LIBFT) .

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
