/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:45:04 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/08 15:22:18 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_clean_instr()
{
	t_lst *tmp;

	if (g_ms->instr == NULL)
    	return ;
	tmp = g_ms->instr;
	while (g_ms->instr != NULL)
	{
		tmp = g_ms->instr->next;
		free(g_ms->instr->str_cmd);
		g_ms->instr->str_cmd = NULL;
		g_ms->instr->file_in = 0;
		g_ms->instr->file_out = 0;
		g_ms->instr->exe_state = 0;
		free(g_ms->instr->str_line);
		free(g_ms->instr->str_aux);
		free(g_ms->instr->str_save);
		free(g_ms->instr->str_aux_save);
		ft_bzero(g_ms->instr, sizeof(t_lst));
   		free (g_ms->instr);
		g_ms->instr = tmp;
	}
	free (tmp);
	tmp = NULL;
	g_ms->instr = NULL;
}
