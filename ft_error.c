/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:20:03 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/06 14:01:21 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// TODO Hacer que el elemento tome el error
	// correspondiente dar un valor hay que llegar
	// a acuerdo respecto a valores err

	// TODO
	// actualizar valor de la var de err al final
	//
	//update_q_mark_variable(42);
void	ft_quote_err(int *sh_err)
{
	printf("%d\n\n\n", *sh_err);
	ft_msg(GN_MSG_02, 2);
	if (*sh_err == 0)
		ft_msg_val(Q_ERR_01, *sh_err);
	else
		ft_msg_val(Q_ERR_02, *sh_err);
	*sh_err = 42;
	ft_updt_err(*sh_err);
}

void	ft_all_char_err(int *sh_err, char *str, int type)
{
	ft_msg(GN_MSG_02, 2);
	if (type == 1)
		ft_msg(T_ERR_01, 2);
	else if (type == 2)
		ft_msg(T_ERR_02, 2);
	ft_msg(str, 2);
	ft_msg("\'\n", 2);
	if (type == 1)
	{
		*sh_err = 258;
		ft_updt_err(*sh_err);
	}
	else if (type == 2)
		*sh_err = 13;
}

void	ft_updt_err(int err_n)
{
	g_ms->err_n = err_n;
	ft_add_local_env(ft_strdup("?"), ft_itoa(err_n));
}

void	ft_prn_view(int sh_err, char *str)
{
	int	a;

	ft_msg_ret(str, 1);
	a = sh_err;
	ft_updt_err(sh_err);
}

// void	error_msg_relative_to_file(char *file, t_nod *node)
// {
// 	char	*str;

// 	node->launch = KO;
// 	str = strerror(errno);
// 	ft_putstr_fd("minishell: ", 2);
// 	ft_putstr_fd(file, 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putstr_fd("\n", 2);
// 	update_q_mark_variable(1);
// 	if (node->p_nbr == g_shell->n_proc)
// 		g_shell->assign_error = KO;
// }

void	ft_write_file_err(t_lst *lst, char *file)
{
	lst->exe_state = FAIL;
	ft_msg(GN_MSG_02, 2);
	ft_msg(file, 2);
	ft_msg(": ", 2);
	ft_msg(strerror(errno), 2);
	ft_msg("\n", 2);
	ft_updt_err (1);
	if (lst->el_nbr == g_ms->prcs_n)
		g_ms->flg_err = FAIL;
}


