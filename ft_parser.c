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

int	ft_parser(t_ms *s)
{
	char	*straux;

	straux = s->str;
	while (*straux)
	{
		if (ft_isspace(*straux))
			*straux = ' ';
		straux++;
	}
	g_ms->pars_cmd = ft_strdup(g_ms->str);
	g_ms->to_clean = g_ms->pars_cmd;
	if (ft_quotes_threat(&g_ms->err_n, &g_ms->str)
		|| ft_redir_pipes(&g_ms->err_n, &g_ms->str))
	{
		free(s->pars_cmd);
		free(s->str);
		return (1);
	}
	return (0);
}
