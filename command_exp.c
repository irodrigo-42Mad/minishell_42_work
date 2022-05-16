/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:05:13 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/16 10:11:36 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"

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
/*
int	main(void)
{
	char	*aux;
	char	*cadena;
	char	*other;
	int		len;
	int		pos;
	size_t	end;
	int		begin;

	aux = "echo \"                \"";
	other = "echo \"hola \'que\' $haces";
	if (aux)
	{
		pos = 0;
		len = ft_strlen(aux);
		while (pos < len)
		{
			if (aux[pos] == '\"' || aux[pos] == '\'')
			{
				begin = ++pos;
				if (aux[pos - 1] == '\'')
					end = ft_extract_content(1, aux, pos);
				if (aux[pos - 1] == '\"')
					end = ft_extract_content(2, aux, pos);
				cadena = (char *) malloc (sizeof(char) * (end + 1));
				printf("%zu\n", end);
				ft_strnlcpy(cadena, other, begin -1, (end + 1));
				ft_set_cmd(aux, cadena, pos, end);
				pos += ++end;
				free(cadena);
			}
			pos++;
		}
	}
}
*/
