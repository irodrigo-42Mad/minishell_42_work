# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 11:37:33 by mgrau             #+#    #+#              #
#    Updated: 2022/06/07 11:37:36 by mgrau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## proyect configuration
NAME		= minishell
##source routes
HEADERS		=   executer.h minishell.h mshellcmd.h mshellhead.h mshellmsg.h sh_struct.h

BUILTINS	=   ./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/exit.c \
				./builtins/export.c ./builtins/print_env.c ./builtins/pwd.c ./builtins/unset.c

SRC			=   adv_redir.c $(BUILTINS) builtin_utils.c child_manager.c command_exp.c \
				env_adition.c env_defs.c exec_utils.c executer.c ft_exportfnc2.c \
				ft_search_edata.c fd_utils.c free_auxfn.c ft_clean_obj.c ft_clean_quotes.c \
				ft_cleaning.c ft_comma.c ft_count_elm.c ft_environ_str.c ft_erase_redir.c \
				ft_error.c ft_exec_redir.c ft_exit_clean.c ft_exportfncs.c ft_fillstr_cmd.c \
				ft_hdoc_engine.c ft_heredoc.c ft_initial_redirection.c ft_initialize.c\
				ft_local_env.c ft_memory.c ft_msg_prn.c ft_mshell_aux.c ft_nodeparse.c \
				ft_parser.c ft_prompt_ctrl.c ft_sh_aux.c ft_sigint_acts.c ft_sigint_ctrl.c \
				ft_strfile.c ft_strfile_aux.c ft_string_th_utils.c ft_string_threat.c \
				ft_var_exp_alloc.c ft_var_exp_utils.c ft_var_expand.c mini.c mini_utils.c \
				pathfinder.c try_one.c ft_one_erase.c ft_remove_comma.c

##auxiliar elements routes
LIBFT_PATH  =   libft

GNL_PATH    =   gnl/get_next_line.c

######include readline flags

#42 system particular instalation
RLINE_FLG_I42 =-L/Users/irodrigo/.brew/Cellar/readline/8.1.2/lib
RLINE_INC_I42 =-I/Users/irodrigo/.brew/Cellar/readline/8.1.2/include
RLINE_FLG_M42 =-L/Users/mgrau/.brew/Cellar/readline/8.1.2/lib
RLINE_INC_M42 =-I/Users/mgrau/.brew/Cellar/readline/8.1.2/include

#General personal computer instalation
RLINE_FLG = -L/usr/local/opt/readline/lib
RLINE_INC = -I/usr/local/opt/readline/include/

# compiler information
CC = gcc
OTHER = -Wall -Werror -Wextra
CFLAGS = -O3 -lreadline $(OTHER)

# other instructions
RM = rm -f
MAKE = make
.PHONY: clean fclean all re normi

all: $(NAME)

$(NAME): $(SRC)
	@$(MAKE) -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(LIBFT_PATH)/libft.a $(GNL_PATH) $(SRC) -o $(NAME) $(RLINE_FLG_M42) $(RLINE_INC_M42)
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
	norminette $(HEADERS) $(SRC) $(BUILTINS)
