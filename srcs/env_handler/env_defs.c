/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_defs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:18 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:31:23 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** handle_defs **
	it goes through the list of lines cmd and clears 
	the portions that are enviroment definitions adding the to envar list
	is it a definition?
		 as this is a definition wegot name=aux2, we do a ft_substrn of the first part
		 and get the second part moving through the chain up to name +1 positions
		 we add the newly made var to env list
		 we clear already defined
		 we check again all our list
*/

void	handle_defs(char **cmd)
{
	char	*name;
	char	*value;

	if (is_def(*cmd) == TRUE)
	{
		name = def_name(*cmd);
		value = *cmd + ft_strlen(name) + 1;
		add_def(name, value);
		clear_cmd(cmd);
		handle_defs(cmd);
	}
}

/*
** is_def **
	recorremos cadena y comprobamos que es una definicion buscando '='
*/

int	is_def(char *str)
{
	if (!str)
		return (0);
	while (ft_isalnum(*str) || *str == '_')
		str++;
	if (*str == '=')
		return (1);
	return (0);
}

/*
** def_name **
	recorremos cadena y devolvemos porcion correspondiente a nombre
*/

char	*def_name(char *str)
{
	int		len;
	char	*name;

	len = 1;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	if (*(str + len) == '?')
		return (ft_strdup("?"));
	name = ft_substr(str, 0, len);
	return (name);
}

/*
** add_def **
	there is an existing value on our list
	with same name we overwrite, otherwise we create a new value
*/

void	add_def(char *name, char *value)
{
	char	*prev_value;

	prev_value = prev_env_value(name);
	if (!prev_value)
		add_value_env(name, value);
	else
	{
		free(prev_value);
		overwrite_env_value(name, value);
	}
}

/*
** clear_cmd **
	cmd[0] esta vacio tras pasar por nuestras funciones
	de adicion a env, hacemos una copia de este a nuestro temp
	temp pasa los datos desde la posicion 1 al nuevo cmd,
	moviendo todo el contenido de la cadena 1 posicion hacia adelante
	añadimos final de la cadena
	liberamos el viejo cmd
*/

void	clear_cmd(char **cmd)
{
	char	**temp;
	char	**new_cmd;
	int		i;

	new_cmd = malloc(sizeof(char *) * ft_matrixlen(cmd));
	temp = cmd;
	i = 1;
	while (temp[i])
	{
		new_cmd[i - 1] = ft_strdup(temp[i]);
		i++;
	}
	new_cmd[i - 1] = NULL;
	free_matrix(cmd);
	cmd = new_cmd;
}
