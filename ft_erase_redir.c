/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_erase_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:08:01 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/03 10:53:05 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*erase_redir(char *arg)
{
	int		pos;
	int		scomma;
	char	*dup;
	int		i;

	i = 0;
	pos = ft_strlen(arg);
	scomma = 0;
	dup = NULL;
	dup = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	while (arg[i])
	{
		d_comma(arg[i], &scomma);
		if (((arg[i] == '<') || (arg[i] == '>')) && (scomma == 0))
		{
			pos = i;
			break ;
		}
		i++;
	}
	return (littlecpy(dup, arg, pos));
}

char	*littlecpy(char *dup, char *arg, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		dup[i] = arg[i];
		i++;
	}
	dup[i] = '\0';
	free(arg);
	return (dup);
}

void	d_comma(char c, int *scomma)
{
	if ((c == '\'') || (c == '\"'))
	{
		if ((*scomma == 0) && (c == '\"'))
			*scomma = 2;
		else if ((*scomma == 2) && (c == '\"'))
			*scomma = 0;
		if ((*scomma == 0) && (c == '\''))
			*scomma = 1;
		else if ((*scomma == 1) && (c == '\''))
			*scomma = 0;
	}
}

char	*expand_vars2(char *arg)
{
	int		pos;
	int		scomma;
	char	*dup;
	int		i;

	i = 0;
	pos = 0;
	scomma = 0;
	dup = NULL;
	dup = alloc_expand2(arg, dup);
	while (arg[i])
	{
		d_comma(arg[i], &scomma);
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

char	*alloc_expand2(char *arg, char *dup)
{
	int		i;
	int		length;
	int		scomma;

	i = 0;
	length = 0;
	scomma = 0;
	while (arg[i])
	{
		d_comma(*arg, &scomma);
		if (check_for_dolla(arg[i], arg[i + 1], scomma))
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
