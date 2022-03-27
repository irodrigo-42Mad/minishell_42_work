/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_threat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:02:45 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/10 13:49:02 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_val_envname(int status, char initial)
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

void ft_vname_expand(t_lst *lst, char **file, char **data, int *len)
{
	char *temp;
	char *v_name;
	char *v_val;

	v_name = ft_getname(*data + 1);
	v_val = ft_getvalue(v_name, NOT_EXPRT);
	if (v_val != NULL && **data == '\\')
	{
		temp = ft_strnstr(v_val, " ", ft_getmax_ln(v_val, " "));
		if (temp != NULL)
			printf ("error variable existente"); //añadir variable y nodo  ambiguous_redirect_error(var_name, node);
	}
	if (lst->exe_state == SUCCESS)
		ft_expand_vars(v_val, data, file, len);
	free (v_name);
	free (v_val);
}

void ft_expand_vars(char *v_val, char **data, char **file, int *ln)
{
	size_t x;

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





void	edit_string(char **str, int *i, int envar)
{
	if (**str == '\"')
	{
		**str = '*';
		while (*(++(*str)) != '\"')
		{
			if (**str == '$' && envar == SUCCESS)
			{
				if (ft_val_envname(*(*str + 1), STATE_Q_OK))
				{
					**str = '&';
					(*i)--;
				}
			}
			(*i)++;
		}
	}
	else
	{
		**str = '*';
		while (*(++(*str)) != '\'')
			(*i)++;
	}
	**str = '*';
}

/* computes the length of the string that it has to take out
 * from the piece of command. it should exactly coincide with
 * the mesure of the strings bash uses as args/filenames,
 * exhibiting commas and allowing appended strings to start or
 * ends of comma strings when not spaced. An example of this would
 * be: << "hey""dude" is a heredoc whichs EOF is heydude, and so is
 * << "hey"dude, <<hey"dude", and any combination you can imagine
 * from this. Tedious.
 * This function apart from computing this length it marks with a
 * '*' those chars that will not have to be written inside the
 * final string that has to be gathered. 2 in 1 :D*/
int	ft_str_bash_len(char *str, int envar)
{
	int	x;

	x = 0;
	while (*str == ' ')
		str++;
	while (*str != ' ' && *str != '<' && *str != '>' && *str)
	{
		if (*str == '$' && envar == SUCCESS)
		{
			if (ft_val_envname(*(str + 1), STATE_Q_OK))
				*str++ = '\\';
		}
		if (*str == '\"' || *str == '\'')
			edit_string(&str, &x, envar);
		else
			x++;
		str++;
	}
	return (x);
}

/* A pointer mover. We work with 2 strings, the one that has something inside
 * the commas, and the one that doesnt. This is because its easier to work with
 * a string that does not look inside "" / '' strings, so we can spot which
 * redirection, pipe or whatever is relevant or not when parsing.
 * Minishell  SHOULD NOT workr when given <<, >>, <, >, | inside commas. These
 *will always have to be gathered as arguments for a command. Just like bash.*/
void	ft_set_strpntr(char **tmp, char **empty, char **final, size_t pos)
{
	size_t	new_pos;
	size_t	n_pos2;

	while (**tmp == ' ')
		(*tmp) += 1;
	new_pos = (*tmp - *empty) + 1;
	n_pos2 = new_pos;
	if (final != NULL)
	{
		while (--new_pos > 0)
		{
			if(new_pos <= pos)
				**final = ' ';
			*final += 1;
		}
	}
	while (--n_pos2 > 0)
	{
		if(new_pos <= pos)
			**empty = ' ';
		*empty += 1;
	}
}

void	ft_locate_strptr(int x, char **tmp, char **str)
{
	int	n_location;

	n_location = x;
	while (n_location-- > 0)
		*str = *str + 1;
	n_location = x;
	while (n_location-- > 0)
		*tmp = *tmp + 1;
}