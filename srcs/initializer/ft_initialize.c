/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:53:50 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/22 08:21:07 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_initialize(int m_argc, char **m_env)
{
	ft_bzero(g_ms, sizeof(t_ms));
	g_ms->prompt = ft_strdup("");
	g_ms->argc = m_argc;
	g_ms->sh_env = ft_set_shell_env(SUCCESS, m_env);
	g_ms->sh_envar = ft_set_env_val("?", g_ms->err_n);
	g_ms->state = READING;
	g_ms->flg_err = SUCCESS;
	g_ms->instr = NULL;
}

char	*ft_set_new_shlvl(char *str)
{
	int		shlvl;
	char	*str_shlvl;
	char	*tmp_num;

	shlvl = (ft_atoi(str + 6) + 1);
	tmp_num = ft_itoa(shlvl);
	str_shlvl = ft_strjoin("SHLVL=", tmp_num);
	free (tmp_num);
	return (str_shlvl);
}

char	**ft_set_shell_env(int ch, char **env)
{
	int		i;
	char	**out;

	i = 0;
	if (*env)
	{
		while (env[i])
			i++;
		out = malloc(sizeof(char *) * (i + 1));
		i = 0;
		while (env[i])
		{
			if (!ft_strncmp(env[i], "SHLVL=", ft_strlen("SHLVL=")) \
			&& ch == SUCCESS)
				out[i] = ft_set_new_shlvl(env[i]);
			else
				out[i] = ft_strdup(env[i]);
			i++;
		}
		out[i] = NULL;
	}
	else
		out = ft_set_defaults();
	return (out);
}

char	**ft_set_defaults(void)
{
	char	*path;
	char	**out;

	out = (char **) malloc(sizeof(char *) * 3);
	out[0] = ft_strdup("SHLVL=1");
	path = getcwd(NULL, 0);
	out[1] = ft_strjoin("PWD=", path);
	out[2] = NULL;
	free(path);
	return (out);
}

char	**ft_put_pwd(char **env)
{
	char	*path;
	char	**aux;
	int		i;

	i = 0;
	aux = env;
	while (aux[i])
	{
		if (!ft_strncmp(aux[i], "PWD=", ft_strlen("PWD=")))
			return (env);
		i++;
	}
	aux = malloc(sizeof(char *) * (ft_matrixlen(env) + 2));
	i = 0;
	while ((env)[i])
	{
		aux[i] = ft_strdup((env)[i]);
		i++;
	}
	path = getcwd(NULL, 0);
	aux[i++] = ft_strjoin("PWD=", path);
	aux[i] = NULL;
	free_matrix(env);
	return (aux);
}

/*
//out[i] = NULL;  ojo con esto
//		add_shell_level(&out);
//		add_pwd(&out);
*/
