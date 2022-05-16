/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:00:25 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/16 09:23:51 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_lenv(char *str, int line)
{
	int	x;
	int	ini_len;

	x = ft_str_bash_len(str, SUCCESS);
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

char	*ft_set_new_len(char *str, int ln, int *pos)
{
	char	*v_name;
	char	*v_value;
	int		ln_no_expand;

	v_name = ft_getname(str);
	v_value = ft_getvalue (v_name, NOT_EXPRT);
	ln_no_expand = ft_strlen(v_name);
	if (!*v_value)
		ln = ln - ln_no_expand;
	else
		ln = ln - ln_no_expand + ft_strlen(v_value);
	*pos = *pos - ln_no_expand;
	str += ln_no_expand;
	free(v_name);
	free(v_value);
	return (str);
}
	/* esto hay que revisarlo posible leak si da, añadir la posición en el return
	*/
