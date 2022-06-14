/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_comma.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:59:06 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/08 09:35:14 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_comma(char *tmp)
{
	int		i;
	int		y;
	int		scomma;
	char	*dest;

	i = 0;
	y = 0;
	scomma = 0;
	dest = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	while (tmp[i])
	{
		if (!(r_comma(tmp[i], &scomma, &i, tmp[i + 1])))
		{
			dest[y] = tmp[i];
			i++;
			y++;
		}
		else
			dest[y] = tmp[i];
	}
	dest[y] = '\0';
	free(tmp);
	return (dest);
}

int	r_comma(char c, int *scomma, int *i, char d)
{
	if ((c == '\'') || (c == '\"'))
	{
		if ((*scomma == 0) && (c == '\"'))
			return (add_for_comma(scomma, i, 2));
		else if ((*scomma == 2) && (c == '\"'))
			return (add_for_comma(scomma, i, 0));
		if ((*scomma == 0) && (c == '\''))
			return (add_for_comma(scomma, i, 1));
		else if ((*scomma == 1) && (c == '\''))
			return (add_for_comma(scomma, i, 0));
	}
	else if ((*scomma == 0) && (c == '$') && \
	((!(ft_isspace(d) || (d == '\0')))))
		return (add_for_comma(scomma, i, 0));
	return (0);
}

int	add_for_comma(int *scomma, int *i, int add)
{
	*scomma = add;
	(*i)++;
	return (1);
}
