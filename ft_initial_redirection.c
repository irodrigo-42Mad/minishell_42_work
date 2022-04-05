/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initial_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:52:59 by irodrigo          #+#    #+#             */
/*   Updated: 2022/02/14 11:05:23 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_notvalid(int *sh_err, char **str)
{
	char	*dummy;

	dummy = *str;
	while (*dummy == ' ')
		dummy++;
	if (*dummy == '|')
	{
		ft_all_char_err(sh_err, dummy, 1);
		return (1);
	}
	while (*dummy)
	{
		if (*dummy == '(' || *dummy == ')' || *dummy == ';'
			|| *dummy == '*' || (*dummy == '\\') || *dummy == '&')
		{
			ft_all_char_err(sh_err, dummy, 2);
			return (1);
		}
		dummy++;
	}
	return (0);
}

// tengo que revisar si es necesario pasar la struct del shell
char	*ft_redir_right(int *sh_err, char *str)
{
	str++;
	if (*str == '>')
		str++;
	while (*str == ' ' && *str)
		str++;
	if (*str != '>' && *str != '<' && *str != '|' && *str)
		return (str);
	else
	{
		ft_all_char_err(sh_err, str, 1);
		return (NULL);
	}
}

char	*ft_redir_left(int *sh_err, char *str)
{
	str++;
	if (*str == '<')
		str++;
	while (*str == ' ' && *str)
		str++;
	if (*str != '>' && *str != '<' && *str != '|' && *str)
		return (str);
	else
	{
		ft_all_char_err(sh_err, str, 1);
		return (NULL);
	}
}

static char	*ft_pipe_elm(int *sh_err, char *str)
{
	str++;
	while (*str == ' ' && *str)
		str++;
	if (*str != '|' && *str)
		return (str);
	else
	{
		ft_all_char_err(sh_err, str, 1);
		return (NULL);
	}
}

/*
** tenemos en cuenta la existencia de las redirecciones en el código
*/
int	ft_redir_pipes(int *sh_err, char **str)
{
	char	*mystr;

	mystr = *str;
	if (ft_notvalid(sh_err, str))
		return (1);
	while (*mystr)
	{
		if (*mystr == '>' || *mystr == '<' || *mystr == '|')
		{
			if (*mystr == '<')
				mystr = ft_redir_left(sh_err, mystr);
			else if (*mystr == '>')
				mystr = ft_redir_right(sh_err, mystr);
			else
				mystr = ft_pipe_elm(sh_err, mystr);
			if (!mystr)
				break ;
		}
		else
			mystr++;
	}
	if (!mystr)
		return (1);
	return (0);
}
