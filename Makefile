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
SRC = \
		src/main.c

OPTION = -I. -Ilibft
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : libft/libft.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(OPTION) -L libft/ -lft

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
	make -C minilibx_macos/ clean

re : fclean all
