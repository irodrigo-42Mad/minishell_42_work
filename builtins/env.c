/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:52:19 by mgrau             #+#    #+#             */
/*   Updated: 2022/04/29 11:58:00 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(void)
{
	int		i;
	char	*name;

	i = 0;
	ft_updt_err(0);
	while (g_ms->sh_env[i])
	{
		name = ft_getname(g_ms->sh_env[i]);
		if (*(g_ms->sh_env[i] + ft_strlen(name) + 1) != '\\')
			printf("%s\n", g_ms->sh_env[i]);
		free(name);
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
void	env_entry(char **env, char *name, char *value, int i)
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
