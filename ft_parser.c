/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:14:50 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/19 13:24:25 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(void)
{
	size_t	pos;

	pos = 0;
	while (g_ms->str[pos] != '\0')
	{
		if (ft_isspace(g_ms->str[pos]))
			g_ms->str[pos] = ' ';
		pos++;
	}
	g_ms->pars_cmd = ft_strdup(g_ms->str);
	g_ms->to_clean = g_ms->pars_cmd;
	if (ft_quotes_threat(&g_ms->err_n, &g_ms->pars_cmd)
		|| ft_redir_pipes(&g_ms->err_n, &g_ms->pars_cmd))
	{
		free (g_ms->pars_cmd);
		g_ms->pars_cmd = NULL;
		free (g_ms->str);
		g_ms->str = NULL;
		return (1);
	}
	return (0);
}

size_t	ft_strchlen(char *str, char car)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == car)
			return (i);
	}
	return (i);
}

void	ft_setnewpos(t_ms *s, size_t len)
{
	if (s->str[len + 1] == '|')
	{
		*s->str = *s->str + (len + 1);
		*s->pars_cmd = *s->pars_cmd + (len + 1);
	}
	else
	{
		*s->str = *s->str + len;
		*s->pars_cmd = *s->pars_cmd + len;
	}
}
