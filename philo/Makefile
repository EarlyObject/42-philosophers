# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 11:27:20 by asydykna          #+#    #+#              #
#    Updated: 2021/11/10 13:43:58 by asydykna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c time_mngmt.c threads.c philo_life.c philo_actions.c \
		inits.c

OBJ = $(SRC:.c=.o)

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

VPATH = src include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	norminette ./src ./include

.SILENT: $(OBJ)

.PHONY: all clean fclean re norm