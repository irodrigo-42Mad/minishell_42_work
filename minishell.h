/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:30:23 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/12/03 13:51:22 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h> //strcmp
# include <limits.h>
# include <signal.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "mshellhead.h"
# include "mshellcmd.h"
# include "mshellmsg.h"

/*
** BOOL constants
*/
# define TRUE	1
# define FALSE	0

/*
** system color definition
*/
# define ANSI_RED     "\x1b[31m"
# define ANSI_GREEN   "\x1b[32m"
# define ANSI_YELLOW  "\x1b[33m"
# define ANSI_BLUE    "\x1b[34m"
# define ANSI_MAGENTA "\x1b[35m"
# define ANSI_CYAN    "\x1b[36m"
# define ANSI_RESET   "\x1b[0m"

/*
** system paths
*/
# define TMP_PATH	"/tmp/"

// system constants
# define FD_IN			0
# define FD_OUT			1
# define FD_ERR			2

// general state
# define FAIL			0
# define SUCCESS		1

// signal status macros
# define READING		0
# define H_DOC_CMD		1
# define EXECUTING		2

enum e_exp_opts{
	NOTDEF		=	0,
	DEFINED		=	1,
	REDEFINED	=	2,
	EXP_ERR		=	3
};

/*
** Primary stucture
*/
typedef struct s_ms
{
	pid_t	sh_pid;
	char	*prompt;
	char	*str;
	char	*cmd;
	char	*lastcmd;
	char	*flag;
	int		state;
	int		err_n;
}				t_ms;

t_ms	*mini;

// aux printing functions
void		ft_put_banner(void);

// auxiliary shell functions
// ft_sh_aux.c
size_t		ft_max_ln(const char *s1, const char *s2);


// memory threatment functions
// ft_memory.c
void		ft_free_two(void *s1, void *s2);

// prompt configuration
// ft_prompt_ctrl.c
const char	*ft_set_prompt(t_ms *s);
char 		*ft_create_prompt(t_ms *s);



// quotes parsing
// ft_comma.c
int			ft_quotes_threat(char **str);
char		*dquotes(char *str, int *sh_err);
char		*squotes(char *str, int *sh_err);

// redirections threatment
// ft_initial redirections.c
int			ft_redir_pipes(int *sh_err, char **str);
char		*ft_redir_right(int *sh_err, char *str);
char		*ft_redir_left(int *sh_err, char *str);

// signal functions
// files
//		ft_sigint_ctrl.c
//		ft_sigint_acts.c
void		ft_set_signal(t_ms *t_shl);
void		ft_sigint_ctrlc(int signal);
void		ft_sigint_ctrld(int signal);
void		ft_sigint_ctrlc_child(int signal);

// printing functions
// file ft_msg_prn.c
void		ft_msg(char *str, int output);
void		ft_msg_ret(char *str, int output);
int			ft_msg_val(char *str, int err_val);

// printing error functions
// file ft_error.c
int			ft_error(char *str, int err_n);
void		ft_quote_err(int *sh_err);
void		ft_all_char_err(int *sh_err, char *str, int type);
void		ft_prn_view(int sh_err, char *str);
//void	ft_updt_err(int err_n );// en este falta algo
void		ft_updt_err(int err_n, t_ms *my_shell);

// shell
void		initialize(t_ms *s);
void		get_cmd(t_ms *s);
void		cmd_exit(t_ms *s);
void		cmd_echo(t_ms *s);
void		cmd_pwd(t_ms *s);
//char	*get_cwd(char *buffer, size_t size);
void		cmd_notfound(t_ms *s);

// aux shell clean functions
void		ft_clean_all(t_ms **s);

#endif
