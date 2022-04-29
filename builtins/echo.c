/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:51:58 by mgrau             #+#    #+#             */
/*   Updated: 2022/04/29 11:52:00 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (arg[++i] && !ft_strncmp(arg[i], "-n", ft_getmax_ln(arg[i], "-n")))
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
