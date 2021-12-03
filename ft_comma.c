/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comma.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:23:06 by irodrigo          #+#    #+#             */
/*   Updated: 2021/11/25 10:22:11 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dquotes(char *str, int *q_err)
{
	str++;
	while (*str != '\"' && *str)
		*str++ = ' ';
	if (!*str)
	{
		ft_quote_err(q_err);
		return (NULL);
	}
	else
		return (str);
	return (str);
}

char	*squotes(char *str, int *q_err)
{
	str++;
	while (*str != '\'' && *str)
		*str++ = ' ';
	if (!*str)
	{
		ft_quote_err(q_err);
		return (NULL);
	}
	else
		return (str);
	return (str);
}

/* 
 ** str is duplicate from imput formatted and separated with
 ** spaces redirect simbols and doble mayor are not modified
 ** not error generated with mayor or minor signs
 ** initial value
 **      ls -l ">> c << wc -l >> >> > "
 ** final value
 **      ls -l
*/

// TODO revisar count

int	ft_quotes_threat(char **str)
{
	char	*aux;
	int		count;
	int		q_err;

	count = 0;
	q_err = 0;
	aux = *str;
	while (*aux)
	{
		if (*aux == '\"' || *aux == '\'')
		{
			count++;
			if (*aux == '\"')
				aux = dquotes(aux, &q_err);
			else
				aux = squotes(aux, &q_err);
			if (!aux)
				return (1);
		}
		aux++;
	}
	return (0);
}
