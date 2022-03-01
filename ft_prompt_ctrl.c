/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_ctrl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:52:05 by irodrigo          #+#    #+#             */
/*   Updated: 2022/02/12 10:42:16 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*ft_set_prompt(t_ms *s)
{
	char	*prmpt;

	prmpt = ft_create_prompt(s);
	if (!(s->prompt[0] == '\0'))
		s->prompt = prmpt;
	else
	{
		if (!ft_strncmp(s->prompt, prmpt, ft_getmax_ln(s->prompt, prmpt)))
			free(prmpt);
		else
		{
			free(s->prompt);
			s->prompt = prmpt;
		}
	}
	//g_ms->state = SUCCESS;
	// hay que poner el contador de procesos
	//g_ms->err_n = 0;
	return ((const char *)s->prompt);
}

char	*ft_create_prompt(t_ms *s)
{
	char	*prmpt;
	char	*cur_work_dir;
	char	*work;
	char	*aux;

	write(2, "\n", 1);
	cur_work_dir = getcwd(NULL, 0);
	work = cur_work_dir;
	aux = ft_strjoin(ANSI_CYAN, work);
	ft_bzero (cur_work_dir, ft_strlen(cur_work_dir));
	free (cur_work_dir);
	work = NULL;
	if (s->err_n == 0)
		work = ft_strjoin(aux, ANSI_GREEN);
	else
		work = ft_strjoin(aux, ANSI_RED);
    //s->flag = SUCCESS;

	ft_bzero(aux, ft_strlen(aux));
	free(aux);
	aux = ft_strjoin(work, " > ");
	ft_bzero(work, ft_strlen(work));
	free (work);
	prmpt = ft_strjoin(aux, ANSI_RESET);
	ft_bzero(aux, ft_strlen(aux));
	free (aux);
	//ft_free_two(work, aux);
	return (prmpt);
}
