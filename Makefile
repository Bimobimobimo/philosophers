# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 16:34:46 by lcollong          #+#    #+#              #
#    Updated: 2025/03/06 17:52:22 by lcollong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME = philo
CC = cc
CFLAGS += -Wall -Wextra -Werror -g 
#-fsanitize=thread

SRC_DIR = src
OBJ_DIR = obj

SRC = 	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/parsing_utils.c \
		$(SRC_DIR)/mutexes.c \
		$(SRC_DIR)/threads.c \
		$(SRC_DIR)/simulation.c \
		$(SRC_DIR)/time.c \
		$(SRC_DIR)/cleanup.c \
		$(SRC_DIR)/print.c

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
