/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:05:13 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:35:28 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../libft/libft.h"

size_t	ft_extract_content(int flg, char *str, size_t pos)
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

size_t	ft_set_cmd(char *origin, char *piece, size_t pos, size_t len)
{
	size_t	act_len;
	size_t	mi_pos;

	act_len = 0;
	mi_pos = pos - 1;
	if (origin)
	{
		printf("act_len: %zu\n", act_len);
		printf("len: %zu\n", len);
		while (act_len < len)
		{
			origin[mi_pos] = piece[act_len];
			mi_pos++;
			act_len++;
		}
	}
	return ((size_t) 0);
}
		/*
		// desde este punto lo que tengo que hacer es recorrer hasta el fin
		// cambiando todos los elementos una posición hacia atras


		//printf ("ORIGIN: %s\n", origin);
		//printf ("PIECE: %s\n", piece);
		*/
