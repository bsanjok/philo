# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 13:54:50 by sbhatta           #+#    #+#              #
#    Updated: 2023/09/03 12:59:58 by sbhatta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Werror -Wall -pthread -g
NAME = philo

SRC = ./src/main.c ./src/despair.c ./src/gluttony.c ./src/init.c ./src/print.c ./src/sloth.c \
		./src/wrath.c ./src/utils.c ./src/checker.c ./src/take_forks.c
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME): $(OBJ)
		$(CC) -o $@ $^

%.o:%.c
		$(CC) -c $(CFLAGS) -o $@ $<

clean:
		rm -f $(OBJ)
		
fclean: clean
		rm -f $(NAME)
		
re:		fclean all
		
.PHONY: all clean fclean