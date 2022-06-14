# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 11:37:33 by mgrau             #+#    #+#              #
#    Updated: 2022/06/14 09:27:14 by mgrau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## proyect configuration
NAME		= minishell
##source routes
HEADERS		=   ./includes/executer.h ./includes/minishell.h ./includes/mshellcmd.h ./includes/mshellhead.h ./includes/mshellmsg.h ./includes/sh_struct.h

BUILTINS	=   ./srcs/executer/builtins/cd.c ./srcs/executer/builtins/echo.c ./srcs/executer/builtins/env.c ./srcs/executer/builtins/exit.c \
				./srcs/executer/builtins/export.c ./srcs/executer/builtins/print_env.c ./srcs/executer/builtins/pwd.c ./srcs/executer/builtins/unset.c ./srcs/executer/builtins/builtin_utils.c

CLEANER		=	./srcs/cleaner/free_auxfn.c ./srcs/cleaner/ft_cleaning.c ./srcs/cleaner/ft_memory.c ./srcs/cleaner/ft_clean_obj.c ./srcs/cleaner/ft_error.c \
				./srcs/cleaner/ft_msg_prn.c ./srcs/cleaner/ft_clean_quotes.c ./srcs/cleaner/ft_exit_clean.c

ENV_HANDLER	=	./srcs/env_handler/env_adition.c ./srcs/env_handler/ft_environ_str.c ./srcs/env_handler/ft_local_env.c ./srcs/env_handler/env_defs.c \
				./srcs/env_handler/ft_exportfnc2.c ./srcs/env_handler/ft_search_edata.c ./srcs/env_handler/ft_count_elm.c ./srcs/env_handler/ft_exportfncs.c

EXECVE		=	./srcs/executer/execve/child_manager.c ./srcs/executer/execve/exec_utils.c ./srcs/executer/execve/executer.c ./srcs/executer/execve/fd_utils.c \
				./srcs/executer/execve/pathfinder.c

INITIALIZER	=	./srcs/initializer/ft_initialize.c ./srcs/initializer/ft_prompt_ctrl.c ./srcs/initializer/mini.c ./srcs/initializer/ft_mshell_aux.c \
				./srcs/initializer/ft_sh_aux.c ./srcs/initializer/mini_utils.c

COMMAS		=	./srcs/parser/commas/command_exp.c ./srcs/parser/commas/ft_comma.c ./srcs/parser/commas/ft_remove_comma.c

HEREDOC		=	./srcs/parser/heredoc/ft_hdoc_engine.c ./srcs/parser/heredoc/ft_heredoc.c

INITIAL_PARSER	=	./srcs/parser/initial_parser/ft_nodeparse.c ./srcs/parser/initial_parser/ft_parser.c ./srcs/parser/initial_parser/ft_strfile.c

P_UTILS		=		./srcs/parser/p_utils/ft_fillstr_cmd.c ./srcs/parser/p_utils/ft_strfile_aux.c ./srcs/parser/p_utils/ft_string_threat.c \
					./srcs/parser/p_utils/ft_one_erase.c ./srcs/parser/p_utils/ft_string_th_utils.c ./srcs/parser/p_utils/try_one.c

REDIRECTIONS	=	./srcs/parser/redirections/adv_redir.c ./srcs/parser/redirections/ft_exec_redir.c ./srcs/parser/redirections/ft_erase_redir.c \
					./srcs/parser/redirections/ft_initial_redirection.c

VAR_EXPAND		=	./srcs/parser/var_expand/ft_var_exp_alloc.c ./srcs/parser/var_expand/ft_var_exp_utils.c ./srcs/parser/var_expand/ft_var_expand.c

SIGNALS			= ./srcs/signals/ft_sigint_acts.c	./srcs/signals/ft_sigint_ctrl.c

SRC			=	$(INITIAL_PARSER) $(BUILTINS)  $(CLEANER) $(ENV_HANDLER) $(EXECVE) $(INITIALIZER) \
				$(COMMAS) $(HEREDOC) $(P_UTILS) $(REDIRECTIONS) $(VAR_EXPAND) $(SIGNALS)

##auxiliar elements routes
LIBFT_PATH  =   libft

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
	@$(CC) $(CFLAGS) $(LIBFT_PATH)/libft.a $(SRC) -o $(NAME) $(RLINE_FLG_M42) $(RLINE_INC_M42)
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
	norminette $(HEADERS) $(SRC)
