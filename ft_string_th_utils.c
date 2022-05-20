/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_th_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:02:13 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/20 12:03:02 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new_pos = ft_strlen(*empty) - ft_strlen(*tmp) + 1;
	n_pos2 = new_pos;
	if (final != NULL)
	{
		while (--new_pos > 0)
		{
			if (new_pos <= pos)
				**final = ' ';
			*final += 1;
		}
	}
	while (--n_pos2 > 0)
	{
		if (n_pos2 <= pos)
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
