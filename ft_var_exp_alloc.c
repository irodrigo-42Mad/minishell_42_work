/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_exp_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:35:27 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/20 07:57:25 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_expand(char *arg, char *dup)
{
	int		i;
	int		length;
	int		scomma;

	i = 0;
	length = 0;
	scomma = 0;
	while (arg[i])
	{
		detect_comma(*arg, &scomma);
		if ((arg[i] == '$') && (scomma <= 0) && \
		(arg[i + 1]) && (arg[i + 1] != '.'))
		{
			if (*(arg + 1) == 63)
				length = var_n_length(length, &i);
			else if (ft_isdigit(*(arg + 1)))
				i = i + 2;
			else
				length = length + var_length(arg, &i);
		}
		else
			one_more2(&length, &i);
	}
	return (malloc_zstart(dup, length + 1));
}

char	*malloc_zstart(char *dup, int length)
{
	dup = malloc(sizeof(char *) * (length));
	dup[0] = '\0';
	return (dup);
}

int	var_length(char *arg, int *i)
{
	int		y;
	int		envl;
	int		length;

	length = 0;
	y = 0;
	while (g_ms->sh_env[y])
	{
		envl = envl_calc(y);
		if (ft_strncmp((arg + ((*i) + 1)), \
		g_ms->sh_env[y], \
		envl) == 0)
		{
			length = ft_strlen(g_ms->sh_env[y]) - (envl + 1);
			*i = (*i) + envl - 1;
			return (length);
		}
		else if (!(g_ms->sh_env[++y]))
		{
			(*i)++;
			while (arg[*i] && (!(ft_isspace(arg[*i]))) && (arg[*i] != '$') \
			&& (arg[*i] != '\'') && (arg[*i] != '\"'))
				(*i)++;
		}
	}
	return (length);
}

void	detect_comma(char c, int *scomma)
{
	if ((c == '\'') || (c == '\"'))
	{
		if ((*scomma == 0) && (c == '\"'))
			*scomma = -1;
		else if ((*scomma == -1) && (c == '\"'))
			*scomma = 0;
		if ((*scomma == 0) && (c == '\''))
			*scomma = 1;
		else if ((*scomma == 1) && (c == '\''))
			*scomma = 0;
	}
}
