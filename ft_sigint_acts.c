/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint_acts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:52:05 by irodrigo          #+#    #+#             */
/*   Updated: 2022/02/07 14:18:34 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_ctrlc(int signal)
{
	(void)signal;
	ft_msg("\n\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_updt_err(1);
}
// catch value with true

void	ft_sigint_ctrld(int signal)
{
	(void)signal;
	ft_msg("\n", 2);
}

void	ft_sigint_ctrlc_child(int signal)
{
	(void)signal;
	kill(g_ms->sh_pid, SIGINT);
	ft_msg("Quit: 3\n", 1);
	g_ms->flag = FAIL;
	ft_updt_err(131);
}

void	ft_stop_all_process(int signal)
{
	int		i;
	t_lst	*elm;

	(void)signal;
	elm = g_ms->instr;
	i = g_ms->prcs_n + 1;
	while ((--i) > 0)
	{
		elm->exe_state = FAIL;
		elm = elm->next;
	}
	write(2, "\n", 1);
	ft_updt_err(1);
	g_ms->flg_err = FAIL;
	g_ms->state = EXECUTING;
}