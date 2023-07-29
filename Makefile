# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 13:54:50 by sbhatta           #+#    #+#              #
#    Updated: 2023/07/23 15:56:50 by sbhatta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Werror -Wall -pthread
NAME = philo

SRC = ./src/main.c
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