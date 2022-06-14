/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_erase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:52:25 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:36:34 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*one_erase_redir(char *arg)
{
	int		pos;
	int		scomma;
	char	*dup;
	int		i;
	int		end;

	i = 0;
	pos = ft_strlen(arg);
	end = ft_strlen(arg);
	scomma = 0;
	dup = NULL;
	dup = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	while (arg[i])
	{
		d_comma(arg[i], &scomma);
		if (((arg[i] == '<') || (arg[i] == '>')) && (scomma == 0))
		{
			one_erase_logic(arg, &i, &pos, &end);
			break ;
		}
		i++;
	}
	return (one_littlecpy(dup, arg, pos, end));
}

void	one_erase_logic(char *arg, int *i, int *pos, int *end)
{
	(*pos) = (*i);
	(*i)++;
	if ((arg[(*i)] == '<') || (arg[(*i)] == '>'))
		(*i)++;
	while (ft_isspace(arg[(*i)]))
		(*i)++;
	while ((arg[(*i)]) && ((arg[(*i)] != '<') \
	&& (arg[(*i)] != '>')) && (!(ft_isspace(arg[(*i)]))))
	{
		(*i)++;
		(*end) = (*i);
	}
}

char	*one_littlecpy(char *dup, char *arg, int start, int end)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (i < start)
	{
		dup[y] = arg[i];
		i++;
		y++;
	}
	while (i < end)
		i++;
	while (i < (int)ft_strlen(arg))
	{
		dup[y] = arg[i];
		i++;
		y++;
	}
	dup[y] = '\0';
	free(arg);
	return (dup);
}
