/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_defs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:48:38 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/14 12:48:41 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	handle_defs(char **cmd) 				// it goes through the list of lines cmd and clears the portions that are enviroment definitions adding the to envar list
{
	char	*name;
	char	*value;

	if (is_def(*cmd) == TRUE)					// is it a definition?
	{
		name = def_name(*cmd);					// as this is a definition wegot name=aux2, we do a ft_substrn of the first part
		value = *cmd + ft_strlen(name) + 1;		// and get the second part moving through the chain up to name +1 positions
		add_def(name, value);					// we add the newly made var to env list
		clear_cmd(cmd); 						//limpiamos el cmd de las definiciones ya usadas
		handle_defs(cmd); 						//comprobamos de forma recurrente
	}
}

int	is_def(char *str) //recorremos cadena y comprobamos que es una definicion buscando '='
{
	if (!str)
		return (0);
// carce-bo uses a check here to see if the enviroment beggining is ok
//	if (ft_isvalid_env_start(*str, Q_MARK_KO))
//	{
	while (ft_isalnum(*str) || *str == '_')
		str++;
	if (*str == '=')
		return (1);
//	}
	return (0);
}

char	*def_name(char *str) // recorremos cadena y devolvemos porcion correspondiente a nombre
{
	int		len;
	char	*name;

	len = 1; //if using valid env start set to 0
	//
	//if (ft_isvalid_env_start(str[len++], Q_MARK_KO))
	//{
	//just as before it should be alredy checked
	while (ft_isalnum(*str) || *str == '_')
		len++;
	//}
	if (*str == '?')
		return (ft_strdup("?"));
	name = ft_substr(str, 0, len);
	return (name);
}

void	add_def(char *name, char *value) // there is an existing value on our list with same name we overwrite, otherwise we create a new value
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


void	clear_cmd(char **cmd)
{
	char	**temp;
	char	**new_cmd;
	int		i;

	new_cmd = malloc(sizeof(char *) * ft_matrixlen(cmd));
	temp = cmd;
	i = 1;
	while (temp[i]) //cmd[0] esta vacio tras pasar por nuestras funciones de adicion a env, hacemos una copia de este a nuestro temp
	{
		new_cmd[i - 1] = ft_strdup(temp[i]); //temp pasa los datos desde la posicion 1 al nuevo cmd, moviendo todo el contenido de la cadena 1 posicion hacia adelante
		i++;
	}
	new_cmd[i - 1] = NULL; // añadimos final de la cadena
	free_matrix(cmd); //liberamos el viejo cmd
	cmd = new_cmd;
}
