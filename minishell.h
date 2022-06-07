/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatman <hatman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:30:23 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/07 17:09:08 by hatman           ###   ########.fr       */
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

// other constants
# define NOT_EXIST		0
# define EXIST			1

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
# define SIG			3

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

t_ms	*g_ms; // sizeof g_ms has 8 bits at assigment

//initialize structure functions
// ft_initialize.c
char		**ft_set_shell_env(int ch, char **env);
void		ft_initialize(int m_argc, char**m_env);

// set local variable values
//ft_local_env.c
t_sh_var	*ft_set_env_val(char *name, int val);
t_sh_var	*ft_set_envch_val(char *v_name, char *val);
void		free_nodes(t_lst *elm);

int			ft_val_envname(int status, char initial);
int			ft_valid_envcore(char a);

// primary shell functions
// ft_parser.c
int			ft_parser(void);
//int			ft_parser(t_ms *s);

// ft_nodeparse.c
void		ft_prepare_command(void);
//void		ft_prepare_command(t_ms *s);
//t_lst		*ft_newinst(t_ms *s, int *i);
t_lst		*ft_newinst(char *cmd, int *i);
void		ft_lstcmdadd_back(t_lst **lst, t_lst *new);
void		ft_set_paramlst(t_lst *aux);

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
void		ft_set_prompt(void);
void		ft_create_prompt(void);

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
void		ft_redirections(void);
//void		ft_redirections(t_ms *s);
void		ft_check_redir(t_lst *lst);
void		ft_redir(char **str, t_lst *lst, int dir, int mode);
void		ft_clean_hdoc_elm(t_lst *lst);
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
void		ft_state_hdoc(int signal);

// printing functions
// file ft_msg_prn.c
void		ft_msg(char *str, int output);
void		ft_msg_ret(char *str, int output);
int			ft_msg_val(char *str, int err_val);
void		ft_msg_complex(char *str, char *mgs, int output);

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
//t_sh_var	*ft_set_env_val(char *v_name, char *val);
void		ft_get_errstatus(int state);

// ft_environ_str.c
int			ft_set_lenv(char *str, int line);
char		*ft_set_new_len(char *str, int ln, int *pos);

// ft_search.c
char		*ft_getname(char *str);
char		*ft_getvalue(char *name, int call_stat);
char		*ft_localchk_env(char *name, int status);
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
void		ft_expand_vars(char *v_val, char **data, char **file, int *ln);
void		ft_vname_expand(t_lst *lst, char **file, char **data, int *len);
void		ft_set_strandenv(char **file, char **data, t_lst *lst, int *len);
int			ft_str_bash_len(char *str, int envar);
void		ft_exit_error(char *str, int type);
void		ft_chk_lval(char *v_name, char **pr_val);
int			ft_envfind(char *name);
void		ft_alreadydefined(char *v_name, char *v_val);
void		ft_envcreate(char *v_name, char *v_val);
void		ft_recharge_env(char *v_name, char *v_val);
void		ft_add_envglob(char *v_name, char *v_val, int status);
void		ft_redir(char **str, t_lst *lst, int dir, int mode);
void		ft_locate_strptr(int x, char **tmp, char **str);
void		free_ptrs(char *one, char *two, char *three);
char		*set_hdocfname(int exist);
void		ft_heredoc(void);
void		ft_clean_instr(void);
void		ft_set_hdoc(t_lst *lst);
char		*ft_eofcatch(int *hd_num, char **dat_line);
void		ft_hdc_prepareln(t_lst *lst);
void		ft_set_strpntr(char **tmp, char **empty, char **final, size_t pos);
void		ft_pre_clean(void);
void		free_vars(t_sh_var *elm);
int			ft_check_spc(char *str);
int			ft_count_orders(void);
void		ft_quote_cmd(char *str);
void		ft_restore_str_command(void);
void		ft_rebuild_str(t_lst *lst);
void		ft_setlst_type(t_lst *aux);

//ft_var_expand.c
char		*expand_vars(char *arg);
void		detect_comma(char c, int *scomma);
char		*aux_cpy(char *tmp, char *dup, int pos);
char		*var_detected(char *arg, char *dup, int *pos, int *i);
char		*q_mark_det(char *dup, int *pos, int *i, char *arg);
char		*dolla_handler(char *arg, char *dup, int *pos, int *i);
int			heredoc_opener(char *file);
void		node_to_zero(t_lst *aux);
void		ft_clear_str(char *str, t_lst *lst);
void		ft_clean_hdoc_pos(t_lst *elm);
int			var_length(char *arg, int *i);
char		*alloc_expand(char *arg, char *dup);
void		add_one(char *arg, char *dup, int i, int pos);
int			var_n_length(int length, int *i);
void		one_more2(int *a, int *b);
void		add_one_to_up(char *arg, char *dup, int i, int pos);
int			envl_calc(int y);
char		*no_var_found(char *arg, char *dup, int *pos, int *i);
int			ft_dircheck(char *file);
void		ft_indirection(char *file, t_lst *lst);
void		ft_control_out_mode(char *file, t_lst *lst, int mode);
size_t		ft_set_end(char *str, int pos);
size_t		ft_set_quote_pos(int flg, char *str, size_t pos);
int			ft_element_error(char *str, int err_n);
char		*ft_prepare_aux(char *aux);
char		*get_filename(t_lst *lst, size_t *last_pos);
void		set_redirection(t_lst *lst, size_t *pos, int type);
char		*space_in(char *s, int pos);
char		*add_space(char *s);
void		prepare_strline(t_lst	*aux);
void		reconstruction(t_lst	*aux);
void		add_flag(size_t *pos, int *flg, int t);
char		*second_comma(char *s, int i, int *com);
char		*malloc_zstart(char *dup, int length);
void		disaster(void);
char		*trim(char *s);
void		ft_mute_aux(char *str, char *str2);
void		d_comma(char c, int *scomma);
char		*erase_redir(char *arg);
char		*littlecpy(char *dup, char *arg, int pos);
void		prep_strcmd(t_lst *aux);
int			check_for_exp(char c);
char		*expand_vars2(char *arg);
char		*alloc_expand2(char *arg, char *dup);
void		pre_disaster(void);
int			check_for_dolla(char c, char d, int scomma);
char		*remove_comma(char *tmp);
int			r_comma(char c, int *scomma, int *i, char d);
char		*one_erase_redir(char *arg);
char		*one_littlecpy(char *dup, char *arg, int start, int end);
int			add_for_comma(int *scomma, int *i, int add);
void		hdoc_strings(t_lst *lst);
void		hdoc_parse(t_lst *lst, char *tmp, int *begin, int *quotes);
void		get_herename(t_lst *lst, char *tmp, int *begin, int *quotes);
void		look_for_begin(char *tmp, int *begin, int *quotes);
void		one_erase_logic(char *arg, int *i, int *pos, int *end);
void		ft_export_logic(char **argv, int *i);
#endif
