/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatman <hatman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:32:24 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/17 09:55:12 by hatman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Given a cmd line like: echo "this $HOME"
expands $ variable into the one at our env list
$? is implemented  not on norme, ill go ahead and clean it up later*/
int		var_length(char *arg, int *i);
char	*alloc_expand(char *arg, char *dup);

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
		if ((arg[i] == '$') && (scomma <= 0) && \
		(arg[i + 1]) && (arg[i + 1] != '.'))
			dup = dolla_handler(arg, dup, &pos, &i);
		else
		{
			dup[pos] = arg[i];
			dup[pos + 1] = '\0';
		}
		pos++;
		i++;
	}
	dup[pos] = '\0';
	return (dup);
}

char	*alloc_expand(char *arg, char *dup)
{
	int		i;
	int		length;
	int		scomma;
	char	*tmp;

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
			{
				i = i + 2;
				tmp = ft_itoa(g_ms->err_n);
				length = length + ft_strlen(tmp);
				free(tmp);
			}
			else if (ft_isdigit(*(arg + 1)))
				i = i + 2;
			else
				length = length + var_length(arg, &i);
		}
		else
		{
			i++;
			length++;
		}
	}
	dup = malloc(sizeof(char *) * length);
	return (dup);
}

int	var_length(char *arg, int *i)
{
	int		y;
	int		envl;
	int		length;
	char	*tmp;

	length = 0;
	y = 0;
	while (g_ms->sh_env[y])
	{
		tmp = def_name(g_ms->sh_env[y]);
		envl = ft_strlen(tmp);
		free (tmp);
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
			while (arg[*i] && (!(ft_isspace(arg[*i]))))
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
		if ((*scomma == -1) && (c == '\"'))
			*scomma = 0;
		else if ((*scomma == 0) && (c == '\''))
			*scomma = 1;
		if ((*scomma == 1) && (c == '\''))
			*scomma = 0;
	}
}

char	*var_detected(char *arg, char *dup, int *pos, int *i)
{
	int		y;
	int		envl;
	char	*tmp;

	y = 0;
	while (g_ms->sh_env[y])
	{
		tmp = def_name(g_ms->sh_env[y]);
		envl = ft_strlen(tmp);
		free(tmp);
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
		{
			while (arg[*i] && (!(ft_isspace(arg[*i]))))
				(*i)++;
			if ((arg[*i] == '\0'))
			{
				(*i)--;
				(*pos)--;
				return (dup);
			}
			dup[*pos] = arg[*i];
			dup[*pos + 1] = '\0';
		}
	}
	return (dup);
}

char	*q_mark_det(char *dup, int *pos, int *i)
{
	char	*err_n;

	err_n = ft_itoa(g_ms->err_n);
	dup = ft_strcat(dup, err_n);
	(*pos) = ft_strlen(dup) -1;
	(*i) = (*i) + ft_strlen(err_n);
	return (dup);
}

char	*dolla_handler(char	*arg, char *dup, int *pos, int *i)
{
	if (arg[(*i) + 1] == 63)
		dup = q_mark_det(dup, pos, i);
	else if (ft_isdigit(arg[(*i) + 1]))
	{
		(*i)++;
		(*i)++;
		dup[*pos] = arg[*i];
	}
	else
		dup = var_detected(arg, dup, pos, i);
	return (dup);
}
