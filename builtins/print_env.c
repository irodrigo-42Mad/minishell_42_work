/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:46:47 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/14 13:44:47 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	order_env(void)
{
	int			i;
	int			j;
	int			k;
	char		*aux;

	k = ft_matrixlen(g_ms->sh_env) - 1;
	i = 0;
	while (i <= k)
	{
		j = i + 1;
		while (j <= k)
		{
			if (ft_strcmp(g_ms->sh_env[i], g_ms->sh_env[j]) > 0)
			{
				aux = g_ms->sh_env[j];
				g_ms->sh_env[j] = g_ms->sh_env[i];
				g_ms->sh_env[i] = aux;
			}
			j++;
		}
		i++;
	}
}

void	print_env(void)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		order_env();
		add_commas_to_env();
		while (g_ms->sh_env)
		{
			if (*g_ms->sh_env[i] != '*')
				join_print("declare -x", g_ms->sh_env[i]);
			else
				join_print("declare -x", (++(g_ms->sh_env[i])));
			i++;
		}
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	add_commas_to_env(void)
{
	char	*aux_name;
	char	*aux_value;
	char	*aux;
	int		i;

	i = 0;
	while (g_ms->sh_env[i])
	{
		aux = g_ms->sh_env[i];
		aux_name = def_name(aux);
		while (*aux != '=')
			aux++;
		aux_value = ft_strdup(++aux);
		env_entry(aux_name, aux_value, i);
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
void	env_entry(char *name, char *value, int i)
{
	char	*aux1;
	char	*aux2;

	free(g_ms->sh_env[i]);
	if (*value != '\\')
	{
		aux1 = ft_strjoin(name, "=\"");
		aux2 = ft_strjoin(aux1, value);
		g_ms->sh_env[i] = ft_strjoin(aux2, "\"");
		free(aux1);
		free(aux2);
	}
	else
	{
		g_ms->sh_env[i] = ft_strjoin("*", name);
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
