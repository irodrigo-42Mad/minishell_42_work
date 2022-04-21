/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:14:50 by irodrigo          #+#    #+#             */
/*   Updated: 2022/02/14 11:19:52 by irodrigo         ###   ########.fr       */
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
