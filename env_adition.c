/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_adition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:48:31 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/14 12:48:34 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prev_env_value(char *name) 								//we check our env to see if we have a value with this name assigned
{
	int		i;
	char	*temp;
	char	*value;

	temp = ft_strjoin(name, "=");
	i = 0;
	while (g_ms->sh_env[i])											//we go throuh our env var list
	{
		if (!ft_strncmp(g_ms->sh_env[i], temp, ft_strlen(temp)))	//if we find it we store i
			break ;
		i++;
	}
	if (!g_ms->sh_env[i])											//no name found therefore no value found
		value = NULL;
	else
		value = ft_strdup(g_ms->sh_env[i] + ft_strlen(name) + 1);	//name is found, we take value portion if not value we are taking a terminating \0
	free(temp);
	return (value);
}

void	add_value_env(char *name, char *value)									//adds a value to our local env list
{
	t_sh_var	*env_n;
	t_sh_var	**temp;

	env_n = g_ms->sh_envar;
	while (env_n)
	{
		if (!ft_strncmp(env_n->v_name, name, ft_getmax_ln(env_n->v_name, name))) //if name exists but no value is assigned
		{
				free(name);														//we free our name str we are done using it
				free(env_n->v_val);												//we free our v_val storage as we are now assignin it the new value
				env_n->v_val = value;
			break ;
		}
		if (env_n->next == NULL) 												//we save the address of the last node for adding a new env var if needed
			temp = &env_n->next;
		env_n = env_n->next;
	}
	if (!env_n)																	//envar doesnt exist therefore we are assingning a new one to the address stored in temp o to the beggining node
	{
		env_n = new_env_var(name, value);										// we create our new envar with our name and value
		if (temp)
			(*temp) = env_n; 													//if we have an address in temp we use it for storing our new value
		else
			g_ms->sh_envar = env_n;												//if we dont we assing it directly
	}
}

t_sh_var	*new_env_var(char *name, char *value) 									//we create our envar from name value allocating proper space
{
	t_sh_var	*env_n;

	env_n = malloc(sizeof(t_sh_var));
	env_n->v_name = name;
	env_n->v_val = value;
	env_n->next = NULL;
	return (env_n);
}

void	overwrite_env_value(char *name, char *value)							//for overwriting an already assigned value
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strjoin(name, "=");
	while (g_ms->sh_env[i])
	{
		if (!ft_strncmp(g_ms->sh_env[i], aux, ft_strlen(aux)))					//if we find our value
			break ;
		i++;
	}
	free(g_ms->sh_env[i]);
	g_ms->sh_env[i] = ft_strjoin(aux, value);									// we overwrite it
	free(name);
	free(value);
	free(aux);
}
