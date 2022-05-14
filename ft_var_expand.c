/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatman <hatman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:32:24 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/14 10:53:31 by hatman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Given a cmd line like: echo "this $HOME"
expands $ variable into the one at our env list
$? is implemented  not on norme, ill go ahead and clean it up later*/

char *expand_vars(char *arg)
{
	int i;
	int pos;
	int scomma;
	char * dup;

	i = -1;
	pos = 0;
	scomma = 0;
	dup = malloc(sizeof(char) * (ft_strlen(arg)+ 1));
	while (arg[++i])
	{
		detect_comma(arg[i], &scomma);
		if ((arg[i] == '$') && (scomma <= 0) && (arg[i + 1]) && ((arg[i + 1]) != '.'))
			dup = dolla_handler(arg, dup, &pos, &i);
		else
			dup[pos] = arg[i];
		pos++;
	}
	dup[pos] = '\0';
	return (dup);
}

void detect_comma(char c, int *scomma)
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

char *aux_cpy(char *tmp,char *dup, int pos)
{
	int cpy;

	cpy = 0;
	while (cpy < pos)
	{
		tmp[cpy] = dup[cpy];
		cpy++;
	}
	tmp[cpy] = '\0';
	cpy = 0;
	free(dup);
	return(tmp);
}

char *var_detected(char* arg, char *dup, int *pos, int *i)
{
	int y;
	int envl;
	int length;
	char *tmp;

	y = 0;
	length = ft_strlen(arg);
//	printf("length is :%i\n", length);
	while (g_ms->sh_env[y])
	{
		envl = ft_strlen(def_name(g_ms->sh_env[y]));
		if (ft_strncmp(arg + ((*i) + 1), \
		g_ms->sh_env[y], \
		envl) == 0)
		{
			length = length + ft_strlen(g_ms->sh_env[y]) - (envl + 1);
			tmp = malloc(sizeof(char) * (length + 1));
			tmp = aux_cpy(tmp, dup, *pos);
			dup = ft_strcat(tmp, ft_strdup(g_ms->sh_env[y] + envl + 1));
			(*pos) = ft_strlen(dup) - 1;
			(*i) = (*i) + envl - 1;
		}
		else if (!(g_ms->sh_env[++y]))
				(*i)++;
	}
	return(dup);
}

//no funciona bien he de revisarlo
char *q_mark_det(char* arg, char *dup, int *pos, int *i)
{
	int length;
	char *tmp;
	char *err_n;

	err_n = ft_itoa(g_ms->err_n);
	length = ft_strlen(err_n);
	tmp = malloc(sizeof(char) * (ft_strlen(arg) - 1 + length));
	tmp = aux_cpy(tmp, dup, *pos);
	dup = ft_strcat(tmp, err_n);
	(*pos) = ft_strlen(dup) -1;
	(*i) = (*i) + length;
	return(dup);
}

char * dolla_handler(char* arg, char *dup, int *pos, int *i)
{
	if (arg[(*i) + 1] == 63) 
		dup = q_mark_det(arg, dup, pos, i);
	else if (ft_isdigit(arg[(*i) + 1]))
	{
		*i = (*i)+ 2;
		dup[*pos] = arg[*i];
	}
	else
		dup = var_detected(arg, dup, pos, i);
	return(dup);
}