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

const char	*ft_set_prompt(t_ms *s)
{
 	char    *prmpt;

    prmpt = ft_create_prompt(s);
    if (!(s->prompt[0] == '\0'))
        s->prompt = prmpt;
    else
    {
        if (!ft_strncmp(s->prompt, prmpt, ft_max_ln(s->prompt, prmpt)))
            free(prmpt);
        else
        {
            free(s->prompt);
            s->prompt = prmpt;
        }
    }
    return ((const char *)s->prompt);
}

char *ft_create_prompt(t_ms *s)
{
    char    *prmpt;
    char    *cur_work_dir;
    char    *work;
    char    *aux;

    write(2, "\n", 1);
    cur_work_dir = getcwd(NULL, 0);
    // si hace falta simbolo shell hacer un strjoin con los simbolos
	work = cur_work_dir;
    aux = ft_strjoin(ANSI_CYAN, work);
    ft_free_two(work, cur_work_dir);
    if (s->err_n == 0)
        work = ft_strjoin(aux, ANSI_GREEN);
    else
        aux = ft_strjoin(aux, ANSI_RED);
    //s->flag = SUCCESS;
    free(aux);
    aux = ft_strjoin(aux, " > ");
    prmpt = ft_strjoin(aux, ANSI_RESET);
    //ft_free_two(work, aux);
    return (prmpt);
}
