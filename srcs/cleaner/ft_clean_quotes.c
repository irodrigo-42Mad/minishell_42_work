/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:09:14 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:30:41 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quote_cmd(char *str)
{
	int		quote_cnt;
	int		type;
	size_t	i;

	i = 0;
	type = 0;
	quote_cnt = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote_cnt % 2 == 0 && type == 0)
			type = 1;
		if (str[i] == '\"' && quote_cnt % 2 == 0 && type == 0)
			type = 2;
	}
}
