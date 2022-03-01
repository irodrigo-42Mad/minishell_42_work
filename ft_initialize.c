/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:53:50 by irodrigo          #+#    #+#             */
/*   Updated: 2022/02/04 13:48:30 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize(int m_argc, char**m_env)
{
	ft_bzero(g_ms, sizeof(t_ms));
	g_ms->prompt = ft_strdup("");
	g_ms->argc = m_argc;
	g_ms->sh_env = ft_set_shell_env(SUCCESS, m_env);
	g_ms->sh_envar = ft_set_env_val(ft_strdup("?"), ft_itoa(g_ms->err_n));
	g_ms->state = READING;
	g_ms->flg_err = SUCCESS;
	g_ms->instr = NULL;
}

char	*ft_set_new_shlvl(char *str)
{
	int		shlvl;
	char	*str_shlvl;

	shlvl = (ft_atoi(str + 6) + 1);
	str_shlvl = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	return (str_shlvl);
}

char	**ft_set_shell_env(int ch, char **env)
{
	int		i;
	char	**out;

	i = 0;
	while (env[i])
		i++;
	out = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", ft_strlen("SHLVL=")) && ch == SUCCESS)
			out[i] = ft_set_new_shlvl(env[i]);
		else
			out[i] = ft_strdup(env[i]);
		i++;
	}
	out[i] = NULL; // ojo con esto
	if (ch == SUCCESS)
	{
//		add_shell_level(&out);
//		add_pwd(&out);
	}
	return (out);
}
