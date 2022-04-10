/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatman <hatman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:46:47 by mgrau             #+#    #+#             */
/*   Updated: 2022/04/09 12:52:20 by hatman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char **env;
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
void env_free(char **env)
{
	int i;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env[i]);
	free(env);
}
char **copy_env()
{
	int i;
	char **ret;

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
	return(ret);
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

/* ((When called from export with no arguments, ))*/
/* sets name=value to name="value".
 * With the exception that if export has
 * exported some variable that has not been defined, it only pops out
 * when you call export without arguments, with no value or equal 
 * sign. [export a] makes env not show a, but export without arguments
 * will show at the end "declare -x a". I mark these special entries
 * with a \* at the start, so they can be identified and printed or
 * not when necessary.*/
void	env_entry(char **env,char *name, char *value, int i)
{
	char	*aux1;
	char	*aux2;

	free(env[i]);
	if (*value != '\\')
	{
		aux1 = ft_strjoin(name, "=\"");
		aux2 = ft_strjoin(aux1, value);
		env[i] = ft_strjoin(aux2, "\"");
		free(aux1);
		free(aux2);
	}
	else
	{
		env[i] = ft_strjoin("*", name);
		free(name);
		free(value);
	}
}

void	join_print(char *str1, char *str2)
{
	char	*tmp;

	tmp = ft_strjoin(str1, str2);
	ft_putstr_fd(tmp, 1);
	ft_putchar_fd('\n', 1);
	free(tmp);
}
