/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatman <hatman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:32:24 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/06 12:30:19 by hatman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Given a cmd line like: echo "this $HOME"
expands $ variable into the one at our env list
$? is implemented  not on norme, ill go ahead and clean it up later*/

char	*expand_vars(char *arg)
{
	int		pos;
	int		scomma;
	char	*dup;
	int		i;

	i = 0;
	pos = 0;
	scomma = 0;
	dup = NULL;
	dup = alloc_expand(arg, dup);
	while (arg[i])
	{
		detect_comma(arg[i], &scomma);
		if (check_for_dolla(arg[i], arg[i + 1], scomma))
			dup = dolla_handler(arg, dup, &pos, &i);
		else
			add_one_to_up(arg, dup, i, pos);
		pos++;
		i++;
	}
	dup[pos] = '\0';
	return (dup);
}

char	*var_detected(char *arg, char *dup, int *pos, int *i)
{
	int		y;
	int		envl;
	char	*tmp;

	y = 0;
	while (g_ms->sh_env[y])
	{
		envl = envl_calc(y);
		if (ft_strncmp((arg + (*i) + 1), \
		g_ms->sh_env[y], \
		envl) == 0)
		{
			tmp = ft_strdup(g_ms->sh_env[y] + envl + 1);
			dup = ft_strcat(dup, tmp);
			free(tmp);
			(*pos) = ft_strlen(dup) - 1;
			*i = (*i) + envl;
			return (dup);
		}
		else if (!(g_ms->sh_env[++y]))
			return (no_var_found(arg, dup, pos, i));
	}
	return (dup);
}

char	*q_mark_det(char *dup, int *pos, int *i, char *arg)
{
	char	*err_n;

	err_n = ft_itoa(g_ms->err_n);
	dup = ft_strcat(dup, err_n);
	(*pos) = ft_strlen(dup) - 1;
	(*i) = (*i) + ft_strlen(err_n);
	dup[*pos + 1] = '\0';
	if (ft_strlen(err_n) > 1)
	{	
		(*i)--;
		if (arg[*i] == '\0')
		{
			(*i)--;
		}
	}
	free(err_n);
	return (dup);
}

char	*dolla_handler(char	*arg, char *dup, int *pos, int *i)
{
	if (arg[(*i) + 1] == 63)
		dup = q_mark_det(dup, pos, i, arg);
	else if (ft_isdigit(arg[(*i) + 1]))
	{
		(*i)++;
		if (!(arg[(((*i) + 1))]))
			return (dup);
		(*i)++;
		dup[*pos] = arg[*i];
	}
	else
		dup = var_detected(arg, dup, pos, i);
	return (dup);
}

int	check_for_dolla(char c, char d, int scomma)
{
	if ((c == '$') && (scomma <= 0) && \
	(d) && ((d != '.') && \
	(d != ' ') && (d != '\"') \
	&& (d != '\'')))
		return (1);
	return (0);
}
