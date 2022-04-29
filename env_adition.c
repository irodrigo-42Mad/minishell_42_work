/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_adition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:16:09 by mgrau             #+#    #+#             */
/*   Updated: 2022/04/29 10:16:12 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** prev_env_value **
	we check our env to see if 
	we have a value with this name assigned
	we go throuh our env var list
	if we find it we store i
	no name found therefore no value found
	name is found, we take value portion
	if not value we are taking a terminating \0
*/

char	*prev_env_value(char *name)
{
	int		i;
	char	*temp;
	char	*value;

	temp = ft_strjoin(name, "=");
	i = 0;
	while (g_ms->sh_env[i])
	{
		if (!ft_strncmp(g_ms->sh_env[i], temp, ft_strlen(temp)))
			break ;
		i++;
	}
	if (!g_ms->sh_env[i])
		value = NULL;
	else
		value = ft_strdup(g_ms->sh_env[i] + ft_strlen(name) + 1);
	free(temp);
	return (value);
}

/*
** add_value_env **
	adds a value to our local env list
	if name exists but no value is assigned
	we free our name str we are done using it
	we free our v_val storage as we are now assignin it the new value
	we save the address of the last node for adding a new env var if needed
	envar doesnt exist therefore we are assingning a new one to 
	the address stored in temp o to the beggining node
	we create our new envar with our name and value
	if we have an address in temp we use it for storing our new value
	if we dont we assing it directly
*/

void	add_value_env(char *name, char *value)
{
	t_sh_var	*env_n;
	t_sh_var	**temp;

	env_n = g_ms->sh_envar;
	while (env_n)
	{
		if (!ft_strncmp(env_n->v_name, name, ft_getmax_ln(env_n->v_name, name)))
		{
			free(name);
			free(env_n->v_val);
			env_n->v_val = value;
			break ;
		}
		if (env_n->next == NULL)
			temp = &env_n->next;
		env_n = env_n->next;
	}
	if (!env_n)
	{
		env_n = new_env_var(name, value);
		if (temp)
			(*temp) = env_n;
		else
			g_ms->sh_envar = env_n;
	}
}

/*
** new_env_var **
	we create our envar from name value allocating proper space
*/

t_sh_var	*new_env_var(char *name, char *value)
{
	t_sh_var	*env_n;

	env_n = malloc(sizeof(t_sh_var));
	env_n->v_name = name;
	env_n->v_val = value;
	env_n->next = NULL;
	return (env_n);
}

/*
** overwrite_env_value **
	for overwriting an already assigned value
	if we find our value
	we overwrite it
*/

void	overwrite_env_value(char *name, char *value)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strjoin(name, "=");
	while (g_ms->sh_env[i])
	{
		if (!ft_strncmp(g_ms->sh_env[i], aux, ft_strlen(aux)))
			break ;
		i++;
	}
	free(g_ms->sh_env[i]);
	g_ms->sh_env[i] = ft_strjoin(aux, value);
	free(name);
	free(value);
	free(aux);
}
