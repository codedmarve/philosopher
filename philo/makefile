# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 20:45:53 by moduwole          #+#    #+#              #
#    Updated: 2023/02/08 20:45:53 by moduwole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME	=	philo

CC		=	gcc -pthread

CFLAGS	=	-Werror -Wextra -Wall

SRC		=	*.c


all:	$(NAME)

$(NAME):	$(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean:
	rm -rf $(NAME)

re: fclean all
