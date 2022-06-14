/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:54:29 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:33:53 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	order_env(char **env)
{
	int			i;
	int			j;
	int			k;
	char		*aux;

	k = ft_matrixlen(env) - 1;
	i = 0;
	while (i <= k)
	{
		j = i + 1;
		while (j <= k)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				aux = env[j];
				env[j] = env[i];
				env[i] = aux;
			}
			j++;
		}
		i++;
	}
}

void	print_env(void)
{
	char	**env;
	int		i;

	i = 0;
	env = copy_env();
	order_env(env);
	add_commas_to_env(env);
	while (env[i])
	{
		if (*env[i] != '*')
			join_print("declare -x ", env[i]);
		else
			join_print("declare -x ", (++(env[i])));
		free(env[i]);
		i++;
	}
	free(env[i]);
	free(env);
}

void	env_free(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env[i]);
	free(env);
}

char	**copy_env(void)
{
	int		i;
	char	**ret;

	i = 0;
	while (g_ms->sh_env[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (g_ms->sh_env[i])
	{
		ret[i] = strdup(g_ms->sh_env[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	add_commas_to_env(char **env)
{
	char	*aux_name;
	char	*aux_value;
	char	*aux;
	int		i;

	i = 0;
	while (env[i])
	{
		aux = env[i];
		aux_name = def_name(aux);
		while (*aux != '=')
			aux++;
		aux_value = ft_strdup(++aux);
		env_entry(env, aux_name, aux_value, i);
		free(aux_name);
		free(aux_value);
		i++;
	}
}
