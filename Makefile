# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 18:12:02 by tlemma            #+#    #+#              #
#    Updated: 2021/11/02 17:48:52 by tlemma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
CFLAGS = -Wall -Werror -Wextra

RM = rm -f

AR = ar rs

SOURCES = ./src/pipex.c ./src/pipex_utils.c

OBJECTS = $(SOURCES:.c=.o)

LIBFT = $(MAKE) -C ./libft 

$(NAME):
	$(LIBFT)
	$(CC) $(CFLAGS) $(SOURCES) ./libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) -C ./libft clean
	$(RM) $(OBJECTS) $(BONUS_OBJS)

fclean: clean
	$(RM) ./libft/libft.a
	$(RM) $(NAME)

re: fclean all
		
.PHONY: all clean fclean re bonus .c .o