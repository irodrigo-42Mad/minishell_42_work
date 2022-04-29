/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:52:37 by mgrau             #+#    #+#             */
/*   Updated: 2022/04/29 11:53:01 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **args, int call)
{
	int		is_num;

	if (call == 1)
		ft_putstr_fd("exit\n", 2);
	if (!args[1])
		exit(0);
	is_num = check_if_digit(args[1]);
	if (!is_num)
	{
		ft_exit_error(args[1], 0);
		exit(255);
	}
	else
	{
		if (!args[2])
			exit(ft_atoi(args[1]));
		else
			ft_exit_error(args[1], 1);
	}
}

int	check_if_digit(const char *str)
{
	int		is_num;
	size_t	i;

	is_num = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && is_num)
		if (!ft_isdigit(str[i++]))
			is_num = 0;
	return (is_num && i > 0);
}

void	ft_exit_error(char *str, int type)
{
	ft_msg(GN_MSG_03, 2);
	if (type == 0)
		ft_msg_complex(str, T_ERR_03, 2);
	else
	{
		ft_msg(T_ERR_04, 2);
		ft_updt_err(1);
	}
}
