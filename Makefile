# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 16:34:46 by lcollong          #+#    #+#              #
#    Updated: 2025/02/27 13:28:42 by lcollong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME = philo
CC = cc
CFLAGS += -Wall -Wextra -Werror -g -pthread

SRC_DIR = src
OBJ_DIR = obj

SRC = 	$(SRC_DIR)/philo.c \
		$(SRC_DIR)/mutexes.c \
		$(SRC_DIR)/data.c \
		$(SRC_DIR)/utils.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
