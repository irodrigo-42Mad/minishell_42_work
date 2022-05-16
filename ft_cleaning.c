/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:21:27 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/16 09:21:49 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pre_clean(void)
{
	g_ms->state = 0;
	g_ms->flg_err = 0;
	free(g_ms->prompt);
	g_ms->prompt = NULL;
	ft_clean_instr();
	g_ms->prcs_n = 0;
	g_ms->pars_cmd = NULL;
	free (g_ms->str);
	g_ms->str = NULL;
	g_ms->to_clean = NULL;
	g_ms->state = 0;
	g_ms->flg_err = 0;
}
/*
	// if (g_ms->sh_env)
	// 	free_matrix(g_ms->sh_env);
	// if (g_ms->sh_envar)
	//  	free_vars(g_ms->sh_envar);
	// free(g_ms->prompt);
	// g_ms->argc = 0;
	// ft_bzero(g_ms, sizeof(t_ms));
*/
