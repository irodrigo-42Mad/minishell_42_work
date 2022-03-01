# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/07 17:18:02 by eimaz-va          #+#    #+#              #
#    Updated: 2022/02/11 10:36:27 by irodrigo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = *.c

LIBFT_PATH =  libft

GNL_PATH = gnl/get_next_line.c

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -lreadline -L/Volumes/sgoinfre/students/irodrigo/homebrew/Cellar/readline/8.1.2/lib -I/Volumes/sgoinfre/students/irodrigo/homebrew/Cellar/readline/8.1.2/include #-fsanitize=address

#-L/usr/local/Cellar/readline/8.1/lib/ -I/usr/local/Cellar/readline/8.1/include/

RM = rm -f

MAKE = make

.PHONY: clean fclean all re normi

all: $(NAME)

$(NAME): $(SRC)
	@$(MAKE) -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(LIBFT_PATH)/libft.a $(GNL_PATH) $(SRC) -o $(NAME)
	@echo ========= DONE-MAKE-DISASTERSHELL =========

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@echo ========= Clean objects of minishell ====

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@echo ========= FCLEAN-DISASTERSHELL-DONE =======

re: fclean all

normi: 
	norminette