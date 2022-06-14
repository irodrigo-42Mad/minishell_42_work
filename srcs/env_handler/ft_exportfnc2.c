/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportfnc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:03:44 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/14 08:31:40 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
