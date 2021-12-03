/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint_acts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:52:05 by irodrigo          #+#    #+#             */
/*   Updated: 2021/11/28 20:17:52 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_ctrlc(int signal)
{
	(void)signal;
	ft_msg("\n\n", 2);
}

	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();

void	ft_sigint_ctrld(int signal)
{
	(void)signal;
	ft_msg("\n", 2);
}

void	ft_sigint_ctrlc_child(int signal)
{
	(void)signal;
	//kill(g_shell->pid, SIGINT);
	ft_msg("Quit: 3\n", 1);
	//g_shell->assign_error = FAIL;
	//update_q_mark_variable(131);
}
