/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:30:23 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/06 17:30:16 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "sh_struct.h"
# include "gnl/get_next_line.h"
# include <string.h> //strcmp luego se quitará de uso
# include <limits.h>
# include <signal.h>
# include "libft/libft.h"
# include "executer.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "mshellhead.h"
# include "mshellcmd.h"
# include "mshellmsg.h"

/*
** BOOL constants
*/
# define TRUE			1
# define FALSE			0

/*
** system color definition
*/
# define ANSI_RED		"\x1b[31m"
# define ANSI_GREEN		"\x1b[32m"
# define ANSI_YELLOW	"\x1b[33m"
# define ANSI_BLUE		"\x1b[34m"
# define ANSI_MAGENTA	"\x1b[35m"
# define ANSI_CYAN		"\x1b[36m"
# define ANSI_RESET		"\x1b[0m"

/*
** system paths
*/
# define TMP_PATH		"/tmp/"

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

// redirection control
# define UNIQUE			1
# define MULTIPLE		2

// instruction token type
# define PARAM			2
# define COMMAND		1

// Hdoc_utils_macros
# define INITIATE		0
# define ENDING			1

// redirection mode
# define APPEND			1
# define TRUNCATE		2

// error state
# define STATE_Q_OK		1
# define STATE_Q_FAIL	2

// sport status val
# define NOT_EXPRT		0
# define EXPR_CALL		1

# define UNDEF			0


// pending to use this elements
enum e_exp_opts{
	NOTDEF		=	0,
	DEFINED		=	1,
	REDEFINED	=	2,
	EXP_ERR		=	3
};

t_ms	*g_ms;  // sizeof g_ms has 8 bits at assigment

//initialize structure functions
// ft_initialize.c
char		**ft_set_shell_env(int ch, char **env);
void		ft_initialize(int m_argc, char**m_env);

// set local variable values
//ft_local_env.c
t_sh_var	*ft_set_env_val(char *name, char *value);


int 		ft_val_envname(int status, char initial);
int			ft_valid_envcore(char a);


// primary shell functions
// ft_parser.c
int			ft_parser(t_ms *s);

// ft_nodeparse.c
void		ft_prepare_command(t_ms *s);
t_lst		*ft_newinst(t_ms *s, int *i);

// aux printing functions
void		ft_put_banner(void);

// auxiliary shell functions
// ft_sh_aux.c
size_t		ft_getmax_ln(const char *s1, const char *s2);

// memory threatment functions
// ft_memory.c
void		ft_free_two(void *s1, void *s2);

// prompt configuration
// ft_prompt_ctrl.c
const char	*ft_set_prompt(t_ms *s);
char		*ft_create_prompt(t_ms *s);

// quotes parsing
// ft_comma.c
int			ft_quotes_threat(int *sh_err, char **str);
char		*chk_quotes(char type[], char *str, int *sh_err);
char		*dquotes(char *str, int *sh_err);
char		*squotes(char *str, int *sh_err);

// redirections threatment
// ft_initial redirections.c
int			ft_redir_pipes(int *sh_err, char **str);
char		*ft_redir_right(int *sh_err, char *str);
char		*ft_redir_left(int *sh_err, char *str);
// adv_redir.c
void		ft_redirections(t_ms *s);
void		ft_check_redir(t_lst *lst);
void		ft_redir(char **str, t_lst *lst, int dir, int mode);
void		ft_clean_hdoc_elm (t_lst *lst);
// PENDING OF THREATMENT
char		*ft_obtain_file(t_lst *lst, char **str);
void		ft_control_mode(char *file, t_lst *lst, int mode);
void		ft_new_input(char *file, t_lst *lst);
void		move_str_pointers(char **str, char **data, int pos);

// signal functions
// files
//		ft_sigint_ctrl.c
//		ft_sigint_acts.c
void		ft_set_signal(void);
void		ft_sigint_ctrlc(int signal);
void		ft_sigint_ctrld(int signal);
void		ft_sigint_ctrlc_child(int signal);
void		ft_stop_all_process(int signal);
void		ft_state_hdoc(void);

// printing functions
// file ft_msg_prn.c
void		ft_msg(char *str, int output);
void		ft_msg_ret(char *str, int output);
int			ft_msg_val(char *str, int err_val);
void		ft_msg_complex (char *str, char *mgs, int output);

// printing error functions
// file ft_error.c
int			ft_error(char *str, int err_n);
void		ft_quote_err(int *sh_err);
void		ft_all_char_err(int *sh_err, char *str, int type);
void		ft_prn_view(int sh_err, char *str);
void		ft_updt_err(int err_n);
void		ft_write_file_err(t_lst *lst, char *file);

// environment variable value set
// ft_local_env.c
void		ft_add_local_env(char *car, char *err);
t_sh_var	*ft_set_env_val(char *v_name, char *val);

// ft_environ_str.c
int			ft_set_lenv(char *str, int line);
char		*ft_set_new_len(char *str, int ln, int *pos);

// ft_search.c
char		*ft_getname(char *str);
char		*ft_getvalue(char *name, int call_stat);
char    	*ft_localchk_env(char *name, int status);
char		*ft_envchk(char *name);




// shell
void		get_cmd(t_ms *s);
void		cmd_exit(t_ms *s);
void		cmd_echo(t_ms *s);
void		cmd_pwd(t_ms *s);
//char	*get_cwd(char *buffer, size_t size);
void		cmd_notfound(t_ms *s);

// aux shell clean functions
void		ft_clean_all(t_ms **s);

// pendiente de colocar
// pendiente de colocar
// pendiente de colocar
//void		add_to_local_env(char *car, char *err);

size_t		ft_strchlen(char *str, char car);
char		*ft_strtok(char *str, char *delim);
void 		ft_expand_vars(char *v_val, char **data, char **file, int *ln);
void 		ft_vname_expand(t_lst *lst, char **file, char **data, int *len);
void		ft_set_strandenv(char **file, char **data, t_lst *lst, int *len);
int			ft_str_bash_len(char *str, int envar);
void 		ft_exit_error(char *str, int type);
void		ft_chk_lval(char *v_name, char **pr_val);
int			ft_envfind(char *name);
void		ft_alreadydefined(char *v_name, char *v_val);
void		ft_envcreate(char *v_name, char *v_val);
void		ft_recharge_env(char *v_name, char *v_val);
void		ft_add_envglob(char *v_name, char *v_val, int status);
void		ft_redir(char **str, t_lst *lst, int dir, int mode);
void		ft_locate_strptr(int x, char **tmp, char **str);

#endif
