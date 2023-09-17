# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 13:54:50 by sbhatta           #+#    #+#              #
#    Updated: 2023/09/03 20:52:44 by sbhatta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Werror -Wall -pthread -fsanitize=thread -g
OBJ_DIR = ./obj
NAME = philo

GREEN		= \033[1;32m

SRCS = ./src/main.c ./src/despair.c ./src/gluttony.c ./src/init.c ./src/print.c ./src/sloth.c \
		./src/wrath.c ./src/utils.c ./src/checker.c ./src/take_forks.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)Philosophers are ready to go! 👍$(GREEN)"

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJ_DIR)
		
fclean: clean
	rm -f $(NAME)
		
re:	fclean all
		
.PHONY: all clean fclean