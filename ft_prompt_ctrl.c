/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_ctrl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:52:05 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/11 14:31:22 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_set_prompt (void)
{
	//char *prmpt;

	ft_create_prompt();
	//if(!g_ms->prompt[0] == '\0')

}
/*
const char	*ft_set_prompt(void)
{
	char	*prmpt;

	//prmpt = ft_create_prompt();
	system("leaks minishell");
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
*/

void	ft_create_prompt (void)
{
	char	*aux;
	char	*tmp;
	size_t	len;

	if (g_ms->err_n == 0)
	//{
		//write(2, "\n", 1);
		len = ft_strlen(ANSI_GREEN);
	//}
	else
		len = ft_strlen(ANSI_RED);
	//write(2, "\n", 1);
	aux = getcwd(NULL, 0);
	len += (ft_strlen(aux) + ft_strlen(ANSI_CYAN) + 5);
	len += ft_strlen(ANSI_RESET);
	tmp = ft_calloc(len, sizeof(char));
	tmp = ft_strcat(tmp, ANSI_CYAN);
	tmp = ft_strcat(tmp, aux);
	if (g_ms->err_n == 0)
		tmp = ft_strcat(tmp, ANSI_GREEN);
	else
		tmp = ft_strcat(tmp, ANSI_RED);
	tmp = ft_strcat(tmp, " > ");
	tmp = ft_strcat(tmp, ANSI_RESET);
	free(aux);
	aux = NULL;
	g_ms->prompt = tmp;
}
/*
char	*ft_create_prompt(void)
{
	char	*prmpt;
	char	*cur_work_dir;
	char	*work;
	char	*aux;

	work = NULL;
	aux = NULL;
	if (s->err_n == 0)
		write(2, "\n", 1);
	write(2, "\n", 1);
	cur_work_dir = getcwd(NULL, 0);
	prmpt = cur_work_dir;
	work = cur_work_dir;
	aux = ft_strjoin(ANSI_CYAN, work);
	ft_bzero(work, ft_strlen(work));
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
*/
