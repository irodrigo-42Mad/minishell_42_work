/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint_ctrl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:20:23 by irodrigo          #+#    #+#             */
/*   Updated: 2021/11/29 14:04:47 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_signal(t_ms *t_shl)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	if (t_shl->state == READING)
		signal(SIGINT, ft_sigint_ctrlc);
	//else if (t_shl->state == H_DOC_CMD)
	//	wait_for_hdoc_state();
	else
	{
		if (t_shl->sh_pid != 0)
		{
			signal(SIGINT, ft_sigint_ctrld);
			signal(SIGQUIT, ft_sigint_ctrlc_child);
		}
	}
}
