/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_threat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:02:45 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/14 08:36:49 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_val_envname(int status, char initial)
{
	if (status == STATE_Q_OK)
	{
		if (ft_isalpha(initial) || initial == '_' || initial == '?')
			return (1);
	}
	else
	{
		if (ft_isalpha(initial) || initial == '_' || initial == '?')
			return (1);
	}
	return (0);
}

int	ft_valid_envcore(char a)
{
	if (ft_isalnum(a) || a == '_')
		return (1);
	return (0);
}

/* //añadir variable y nodo  ambiguous_redirect_error(var_name, node);*/

void	ft_vname_expand(t_lst *lst, char **file, char **data, int *len)
{
	char	*temp;
	char	*v_name;
	char	*v_val;

	v_name = ft_getname(*data + 1);
	v_val = ft_getvalue(v_name, NOT_EXPRT);
	if (v_val != NULL && **data == '\\')
	{
		temp = ft_strnstr(v_val, " ", ft_getmax_ln(v_val, " "));
		if (temp != NULL)
			printf ("error variable existente");
	}
	if (lst->exe_state == SUCCESS)
		ft_expand_vars(v_val, data, file, len);
	free (v_name);
	free (v_val);
}

void	ft_expand_vars(char *v_val, char **data, char **file, int *ln)
{
	size_t	x;

	x = 0;
	*(*(data)++) = ' ';
	if (!ft_isdigit((*data)[x++]))
	{
		while (ft_isalnum((*data)[x]))
		{
			(*data)[x] = ' ';
			x++;
		}
	}
	**data = ' ';
	*data = *data + x;
	while (*v_val)
	{
		*((*file)++) = *v_val++;
		*ln = *ln - 1;
	}
}

void	ft_set_strandenv(char **file, char **data, t_lst *lst, int *len)
{
	while (lst->exe_state == SUCCESS && *len > 0)
	{
		if (**data == '&' || **data == '\\')
			ft_vname_expand(lst, file, data, len);
		else if (**data != '\\' && **data != '*' && **data != '*' && **data)
		{
			*((*file)++) = **data;
			*((*data)++) = ' ';
			*len = *len - 1;
		}
		else
			*((*data)++) = ' ';
	}
	while (**data == '*')
		*((*data)++) = ' ';
	if (lst->exe_state == SUCCESS)
		**file = '\0';
}
