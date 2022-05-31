/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_comma.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:59:06 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/31 09:26:26 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_comma(char *tmp)
{
	int i;
	int y;
	int scomma;
	char *dest;

	i = 0;
	y = 0;
	scomma = 0;
	dest = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	while (tmp[i])
	{
		if(!(r_comma(tmp[i], &scomma, &i)))
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
	return(dest);
}

int	r_comma(char c, int *scomma, int *i)
{
	if ((c == '\'') || (c == '\"'))
	{
		if ((*scomma == 0) && (c == '\"'))
		{
			*scomma = 2;
			(*i)++;
			return(1);
		}
		else if ((*scomma == 2) && (c == '\"'))
		{
			*scomma = 0;
			(*i)++;
			return(1);
		}
		if ((*scomma == 0) && (c == '\''))
		{
			*scomma = 1;
			(*i)++;
			return(1);
		}
		else if ((*scomma == 1) && (c == '\''))
		{
			*scomma = 0;
			(*i)++;
			return(1);
		}
	}
	return(0);
}