/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:51:58 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:33:30 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_putstr_fd_without_esc_bar(char *str, int fd)
{
	while (*str)
	{
		if (*str != '\\')
			write(fd, str, 1);
		str++;
	}
}

void	ft_echo(char **arg)
{
	int	i;
	int	newline;

	newline = 1;
	i = 0;
	if (!arg[1])
	{
		ft_putstr_fd("\0", 1);
		ft_putstr_fd("\n", 1);
		ft_updt_err(0);
		return ;
	}
	while (arg[++i] && (is_n(arg[i])))
		newline = 0;
	while (arg[i])
	{
		ft_putstr_fd_without_esc_bar(arg[i++], FD_OUT);
		if (arg[i])
			ft_putstr_fd(" ", FD_OUT);
	}
	if (newline == 1)
		ft_putstr_fd("\n", FD_OUT);
	ft_updt_err(0);
}

int	is_n(char *str)
{
	int	i;

	i = 0;
	if (str && (str[0] == '-'))
	{
		i++;
		while ((str[i] == 'n') || (str[i] == 32))
		{
			i++;
			if (str[i] == '\0')
				return (1);
		}
	}
	return (0);
}
