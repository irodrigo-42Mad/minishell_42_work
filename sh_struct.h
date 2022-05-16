/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:56:38 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/16 09:57:49 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_STRUCT_H
# define SH_STRUCT_H
/*
** Node structure
*/
typedef struct s_lst{
	int				el_nbr;
	int				type;
	int				file_in;
	int				file_out;
	int				exe_state;
	pid_t			node_pid;

	size_t			aux_ln;
	char			*herename;	// pending to activate heredoc structure
	int				herequotes;	// set 0 !quotes, 1 squotes  2 dquotess
	int				here_num;
	char			*str_cmd;
	char			**str_args;
	char			*str_line;
	char			*str_aux;
	char			*str_save;
	char			*str_aux_save;

	struct s_lst	*next;
}				t_lst;

/*
** variable structure s_sh_var
**
** members
**	v_name	    char pointer      contains variable name
**  v_val		char pointer	  contains (text) variable value
**  next		self point stct	  pointer to next element
*/

typedef struct s_sh_var
{
	char			*v_name;
	char			*v_val;
	struct s_sh_var	*next;
}				t_sh_var;

/*
** Primary shell stucture
**
** member variables
**
**	sh_pid		pid_t type		Unique process identification for single process
**	prompt		char pointer	stores the string displayed at the system prompt
**	str			char pointer	string read from the command line
**	pars_cmd	char pointer	parsing command
**	to_clean	char pointer
**	lastcmd;	char pointer
**	flag;		char pointer
**	sh_env;		ch db pointer	system environment variable
**	argc		integer			command line argument counter
**	state		integer			execution state control variable
**	err_n		integer			error number if app fails 0 in other case
**	flg_err		integer			error status 0 correct 1 fail
**	prcs_n		integer			total process counter in process list
**	instr		t_list point	parsed instruction list
**	sh_envar	t_sh_var ptr	parsed system variables list
*/
typedef struct s_ms
{
	pid_t		sh_pid;
	char		*prompt;
	char		*str;
	char		*pars_cmd;
	// **** trabajando por aqui ****
	char		*to_clean;
	char		*lastcmd;
	char		*flag;
	char		**sh_env;
	int			pip_count;
	int			argc;
	int			state;
	int			err_n;
	int			flg_err;
	int			prcs_n;
	t_lst		*instr;
	t_sh_var	*sh_envar;
}				t_ms;
#endif
