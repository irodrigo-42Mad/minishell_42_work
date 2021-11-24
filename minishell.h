/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:30:23 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/11/23 15:18:34 by irodrigo         ###   ########.fr       */
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
//# include "gnl/get_next_line.h"
# include "mshellaux.h"
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
** Primary stucture
*/
typedef struct s_ms
{
	char	*str;
	char	*cmd;
	char	*lastcmd;
	char	*flag;
}				t_ms;

// quotes parsing
// ft_comma.c
int		ft_quotes_threat(char **str);
char	*dquotes(char *str, int *q_err);
char	*squotes(char *str, int *q_err);

// aux printing functions
void	ft_put_banner(void);

// printing functions
// file ft_msg_prn.c
void	ft_msg(char *str, int output);
int		ft_msg_val(char *str, int err_val);

// printing error functions
// file ft_error.c
int		ft_error(char *str, int err_n);
void	ft_quote_err(int *q_err);

// shell
void	initialize(t_ms *s);
void	get_cmd(t_ms *s);
void	cmd_exit(t_ms *s);
void	cmd_echo(t_ms *s);
void	cmd_pwd(t_ms *s);
//char	*get_cwd(char *buffer, size_t size);
void	cmd_notfound(t_ms *s);

// aux shell clean functions
void	ft_clean_all(t_ms **s);

#endif
