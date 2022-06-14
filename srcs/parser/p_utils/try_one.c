/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:58:45 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:37:03 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../libft/libft.h"

size_t	ft_set_quote_pos(int flg, char *str, size_t pos)
{
	size_t	last;
	char	quote;

	last = 0;
	if (flg == 1)
		quote = '\'';
	if (flg == 2)
		quote = '\"';
	while (str[pos] != quote && flg > 0)
	{
		if (str[pos] != quote)
		{
			pos++;
			last++;
		}
		else
			flg = 0;
	}
	return (last);
}

size_t	ft_set_end(char *str, int pos)
{
	size_t	last;

	last = 0;
	while ((str[pos] != ' ') && (str[pos]))
	{
		pos++;
		last++;
	}
	return (last);
}

/*
int	try_one(char* aux)
{
	char	*file;
	size_t	pos;
	size_t	len;
	size_t	end;
	size_t	begin;

	len = ft_strlen(aux);
	pos = 0;
	while (pos < len)
	{
		if (aux[pos] == '>' || aux[pos] == '<')
		{
			if (aux[pos + 1] == '>')
			{
				pos += 3;

				***
				if (lst->str_line[pos] == '\"' || lst->str_line[pos] == '\'')
				{
					begin = ++pos;
					if (lst->str_line[pos - 1] == '\'')
						end = ft_set_quote_pos(1, lst->str_line, pos);
					else
						end = ft_set_quote_pos(2, lst->str_line, pos);
				}
				else
				{
					begin = pos;
					end = ft_set_end(aux, pos);
				}
				***

				file = (char *) malloc(sizeof(char) * (end + 1));
				ft_strnlcpy(file, aux, begin -1, (end + 1));
				// en este momento se hace la expansión de variables de entorno
				// y se imprime
				printf("%s\n", file);
				free(file);
			}
		}
		pos++;
	}
	return (0);
}*/
