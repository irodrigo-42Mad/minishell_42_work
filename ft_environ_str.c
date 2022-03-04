/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:00:25 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/04 12:58:27 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_lenv(char *str, int line)
{
	int	x;
	int ini_len;

	x = ft_str_bash_len(*str, SUCCESS);
	ini_len = x;
	if (line == FAIL)
	{
		while (*str == ' ')
			str++;
	}
	while (x > 0)
	{
		if (*str == '\\' || *str == '&')
			str = ft_set_new_len(++str, ini_len, &x);
		else if (*str != '*')
		{
			str++;
			x--;
		}
		else
			str++;
	}
	return (x);
}

char	*ft_set_new_len(char *str, int *i, int ln)
{
	char	*v_name;
	char	*v_value;
	int		length_wo_expansion;

	v_name = ft_getname(str);
	v_value = ft_getvalue (v_name, NOT_EXPRT);
	length_wo_expansion = ft_strlen(v_name);
	free(v_name);
	if (!*v_value)
		ln = ln - length_wo_expansion;
	else
		ln = ln - length_wo_expansion + ft_strlen(v_value);
	*i = *i - length_wo_expansion;
	free(v_value);
	return (str + length_wo_expansion);
}