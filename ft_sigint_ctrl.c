/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint_ctrl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatman <hatman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:20:23 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/17 13:01:22 by hatman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sys/wait.h"

void	ft_state_hdoc(void)
{
	int	state;

	if (!(g_ms->sh_pid == 0))
	{
		signal(SIGINT, ft_stop_all_process);
		wait(&state);
		if (g_ms->flg_err == SUCCESS)
			ft_updt_err(state);
		g_ms->flg_err = SUCCESS;
	}
}

void	ft_set_signal(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	if (g_ms->state == H_DOC_CMD)
		ft_state_hdoc();
	if (g_ms->state == READING)
		signal(SIGINT, ft_sigint_ctrlc);
	else
	{
		if (g_ms->sh_pid != 0)
		{
			signal(SIGINT, ft_sigint_ctrld);
			signal(SIGQUIT, ft_sigint_ctrlc_child);
		}
	}
}
