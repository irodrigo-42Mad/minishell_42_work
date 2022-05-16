/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg_prn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:43:12 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/16 09:32:48 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	// TODO revisar a ver si en alguna ocasion necesitamos
	// devolver el valor de la longitud de la cadena y otros
	// elementos se puede usar ft_putstr_fd
*/

void	ft_msg(char *str, int output)
{
	ft_putstr_fd(str, output);
}

void	ft_msg_ret(char *str, int output)
{
	ft_putstr_fd(str, output);
	ft_putstr_fd("\n", output);
}

int	ft_msg_val(char *str, int err_val)
{
	write (2, str, ft_strlen(str));
	return (err_val);
}

void	ft_msg_complex(char *str, char *mgs, int output)
{
	write (output, str, ft_strlen(str));
	ft_msg(mgs, 2);
}
