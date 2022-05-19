/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillstr_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:06:50 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/19 13:19:10 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_set_flg(char c, int flg)
{
	if (flg == 0)
	{
		if (c == '\'')
			flg = 1;
		if (c == '\"')
			flg = 2;
	}
	else if (flg == 1)
	{
		if (c == '\'')
			flg = 0;
	}
	else
	{
		if (c == '\"')
			flg = 0;
	}
	return (flg);
}

char	*ft_prepare_aux(char *aux)
{
	int	flg;
	int	pos;
	int	len;

	flg = 0;
	pos = -1;
	len = (int)ft_strlen(aux);
	while (++pos < (len) && aux[pos])
	{
		if (aux[pos] == '\"' || aux[pos] == '\'')
		{
			flg = ft_set_flg(aux[pos], flg);
			pos++;
		}
		if (aux[pos] == ' ' && flg == 0)
			aux[pos] = '|';
	}
	return (aux);
}
