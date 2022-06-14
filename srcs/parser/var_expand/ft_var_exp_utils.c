/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_exp_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:33:07 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:37:43 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_one_to_up(char *arg, char *dup, int i, int pos)
{
	dup[pos] = arg[i];
	dup[pos + 1] = '\0';
}

void	one_more2(int *a, int *b)
{
	(*a)++;
	(*b)++;
}

int	var_n_length(int length, int *i)
{
	char	*tmp;

	*i = (*i) + 2;
	tmp = ft_itoa(g_ms->err_n);
	length = length + ft_strlen(tmp);
	free(tmp);
	return (length);
}

int	envl_calc(int y)
{
	int		envl;
	char	*tmp;

	tmp = def_name(g_ms->sh_env[y]);
	envl = ft_strlen(tmp);
	free (tmp);
	return (envl);
}

char	*no_var_found(char *arg, char *dup, int *pos, int *i)
{
	(*i)++;
	while (arg[*i] && (!(ft_isspace(arg[*i]))) \
	&& (arg[*i] != '$') && (arg[*i] != '\'') && (arg[*i] != '\"'))
	{
		(*i)++;
	}
	if ((arg[*i] == '\0') || (arg[*i] == '\'') || (arg[*i] == '\"'))
	{
		(*i)--;
		(*pos)--;
		return (dup);
	}
	else if (arg[*i] == '$')
	{
		(*i)--;
		return (dup);
	}
	dup[*pos] = arg[*i];
	dup[*pos + 1] = '\0';
	return (dup);
}
