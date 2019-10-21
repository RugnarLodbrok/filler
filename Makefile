# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksticks <ksticks@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 20:27:05 by ksticks           #+#    #+#              #
#    Updated: 2019/09/25 15:44:59 by edrowzee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = ksticks.filler
FLAGS = -Wall -Wextra -Werror
SRC_MAIN = src/main.c
SRC_REST = \
		src/map.c \
		src/map_read.c \
		src/piece.c

OPTION = -I. -Ilibft
OBJ_MAIN = $(SRC_MAIN:.c=.o)
OBJ_REST = $(SRC_REST:.c=.o)
OBJ = $(OBJ_MAIN) $(OBJ_REST)


all : $(NAME)

$(NAME) : libft/libft.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(OPTION) -L libft/ -lft

test : libft/libft.a $(OBJ_REST)
	gcc -c tests/tests.c -o tests/tests.o $(OPTION)
	$(CC) -o filler_test.out $(OBJ_REST) tests/tests.o $(OPTION) -L libft/ -lft
	./filler_test.out

%.o: %.c
	@echo compile $(<) "->" $(<:.c=.o)
	$(CC) $(FLAGS) -c $(<) -o $(<:.c=.o) $(OPTION)

libft/libft.a :
	make -C libft/

run : $(NAME)
	@./$(NAME)

clean :
	rm -f $(OBJ)
	make -C libft/ clean

fclean : clean
	rm -f $(NAME)
	make -C libft/ fclean

re : fclean all
