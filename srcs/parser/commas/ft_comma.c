/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comma.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:23:06 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/14 08:35:16 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		ft_quote_err(q_err + 1);
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

int	ft_quotes_threat(int *err, char **str)
{
	char	*aux;
	int		count;

	count = 0;
	aux = *str;
	while (*aux)
	{
		if (*aux == '\"' || *aux == '\'')
		{
			count++;
			if (*aux == '\"')
				aux = dquotes(aux, err);
			else
			{
				(*err)++;
				aux = squotes(aux, err);
			}
			if (!aux)
				return (1);
		}
		aux++;
	}
	return (0);
}
