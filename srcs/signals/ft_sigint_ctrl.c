/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint_ctrl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:20:23 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/14 08:32:54 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "sys/wait.h"

void	ft_state_hdoc(int signal)
{
	g_ms->state = SIG;
	(void)signal;
	rl_on_new_line();
	ft_msg("\n", 1);
	rl_line_buffer[0] = '\0';
	rl_point = 0;
	rl_end = 0;
	rl_redisplay();
	ft_updt_err(1);
}

void	ft_set_signal(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	if (g_ms->state == READING)
	{
		signal(SIGINT, ft_sigint_ctrlc);
	}
	else if (g_ms->state == H_DOC_CMD)
		signal(SIGINT, ft_state_hdoc);
	else
	{
		signal(SIGINT, ft_sigint_ctrlc_child);
		signal(SIGQUIT, ft_sigint_ctrlc_child);
	}
}
