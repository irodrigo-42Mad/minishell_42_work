/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:01:06 by irodrigo          #+#    #+#             */
/*   Updated: 2022/02/14 10:57:56 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fist_parse(t_ms *s)
{
	char	*aux;

	if (!s->str)
		ft_clean_all(&s);
	aux = s->str;
	while (*aux)
	{
		if (ft_isalltab(*aux))
			*aux = ' ';
		aux++;
	}
	if (s->str != NULL)
	{
		free(s->str);
		free(s->pars_cmd);
		return (1);
	}
	s->pars_cmd = ft_strdup(s->str);
	s->lastcmd = s->pars_cmd;
	if (ft_quotes_threat(& s->err_n, &s->lastcmd))
		printf ("estoy en pruebas\n");
	return (0);
}

// TODO Limpiar la historia con clear_history();
// TODO2  rellenar archivo de mensajes en linea correctos
// TODO3  Comprobar bien las funciones de impresion de mensajes

// OJO: funcion en pruebas
void	ft_clean_all(t_ms **s)
{
	ft_bzero(s, sizeof(s));
	free(s);
	exit(ft_msg_val(GN_MSG_01, 0));
}
