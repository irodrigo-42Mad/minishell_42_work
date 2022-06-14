/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:43:22 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 13:36:52 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ch_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	if (argc != 1)
		exit(ft_msg_val(Q_ERR_04, 42));
	g_ms = malloc(sizeof(t_ms));
	if (!g_ms)
		exit(ft_msg_val(M_ERR_01, 42));
	ft_initialize(argc, env);
	ft_put_banner();
		g_ms->sh_pid = 1;
	while (TRUE)
	{
		pre_disaster();
		if (ft_strlen(g_ms->str) > 0 && \
		ft_check_spc(g_ms->str) != 1)
		{
			add_history(g_ms->str);
			disaster();
		}
	}
	ft_pre_clean();
	free (g_ms);
	return (0);
}

void	disaster(void)
{
	if (!ft_parser())
	{
		ft_prepare_command();
		ft_heredoc();
		if (g_ms->state != SIG)
		{
			ft_redirections();
			ft_restore_str_command();
			if (g_ms->state != SIG)
				start_executer();
		}
	}
	ft_pre_clean();
}

void	pre_disaster(void)
{
	g_ms->sh_pid = 1;
	ft_set_signal();
	ft_set_prompt();
	g_ms->flg_err = SUCCESS;
	g_ms->str = readline(g_ms->prompt);
	if ((!(g_ms->str)) && (g_ms->state == READING))
		exit(0);
}
