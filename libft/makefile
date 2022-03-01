# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 12:19:52 by eimaz-va          #+#    #+#              #
#    Updated: 2021/11/22 10:47:07 by irodrigo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft

LNAME = libft.a

SRC = ft_atoi.c ft_strdup.c ft_bzero.c ft_strjoin.c ft_calloc.c \
	  ft_memccpy.c ft_strlcat.c ft_isalnum.c ft_memchr.c \
	  ft_strlcpy.c ft_isalpha.c	ft_memcmp.c	ft_strlen.c ft_isascii.c \
	  ft_memcpy.c ft_strmapi.c ft_isdigit.c ft_memmove.c \
	  ft_strncmp.c ft_isprint.c	ft_memset.c	ft_strnstr.c ft_itoa.c \
	  ft_putchar_fd.c ft_strrchr.c ft_putendl_fd.c ft_strtrim.c \
	  ft_putnbr_fd.c ft_substr.c ft_putstr_fd.c ft_tolower.c ft_isspace.c \
	  ft_toupper.c ft_split.c ft_strchr.c ft_strcmp.c ft_isalltab.c

BONUSSRC = ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstnew_bonus.c \
		   ft_lstadd_front_bonus.c ft_lstiter_bonus.c ft_lstsize_bonus.c \
		   ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c

CFLAGS = -Wextra -Werror -Wall

LFLAGS = -c

OBJ = ${SRC:.c=.o}

OBJB = ${BONUSSRC:.c=.o}

all: $(LNAME)

$(LNAME): $(SRC) libft.h
	@gcc $(CFLAGS) $(LFLAGS) $(SRC)
	@ar rc $(LNAME) $(OBJ)
	@echo ========= Done Libft ====================

bonus: $(SRC) libft.h
	@gcc $(CFLAGS) $(LFLAGS) $(SRC) $(BONUSSRC)
	@ar rc $(LNAME) $(OBJ) $(OBJB)
	@echo ========= Done BonusLibft =========

clean:
	@rm -f $(OBJ) $(OBJB)
	@echo ========= Clean objects of $(NAME) ========

fclean: clean
	@rm -f $(LNAME)
	@echo ========= Flcean Libft done =============

re:	fclean	all
