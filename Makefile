# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/07 17:18:02 by eimaz-va          #+#    #+#              #
#    Updated: 2021/11/18 13:55:28 by irodrigo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = *.c

LIBFT_PATH =  libft

GNL_PATH = gnl/get_next_line.c

CC = gcc

CFLAGS = -Wall -Werror -Wextra -lreadline

RM = rm -f

MAKE = make

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(SRC)
	@$(MAKE) -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(LIBFT_PATH)/libft.a $(GNL_PATH) $(SRC) -o $(NAME)
	@echo ========= DONE-MAKE-MANOLOSHELL =========

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@echo ========= Clean objects of minishell ====

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@echo ========= FCLEAN-MANOLOSHELL-DONE =======

re: fclean all
