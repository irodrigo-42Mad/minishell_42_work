/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportfnc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:03:44 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/06 17:16:14 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chk_lval(char *v_name, char **pr_val)
{
	char	*l_val;

	l_val = ft_getvalue(v_name, EXPR_CALL);
	if (*l_val != '\\')
	{
		free(*pr_val);
		*pr_val = l_val;
	}
	else
		free(l_val);
}