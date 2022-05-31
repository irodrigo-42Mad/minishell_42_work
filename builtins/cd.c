/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:47:45 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/31 12:17:30 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char *str)
{
	char	*s;
	int		i[2];

	ft_updt_err(0);
	i[0] = ft_envfind("PWD");
	if (i[0] == -1)
		ft_add_envglob(ft_strdup("PWD"), getcwd(NULL, 0), 1);
	i[1] = ft_envfind("OLDPWD");
	if (ft_envfind("HOME") != -1)
	{
		if (str != NULL)
			s = check_pwd(str, i[1], ft_envfind("HOME"));
		else
			s = ft_strdup((g_ms->sh_env[ft_envfind("HOME")] + 5));
	}
	else
		s = ft_strdup("HOME UNSET");
	if ((chdir(s) == -1) || (i[0] == -1) || (i[1] == -1))
		cd_error(s);
	else
	{
		cd_env(i);
		ft_updt_err(0);
	}
	free(s);
}

char	*check_pwd(char *str, int opwd, int home)
{
	char	*s;

	s = NULL;
	if (str)
		s = ft_strdup(str);
	else
		s = ft_strdup(g_ms->sh_env[home] + 5);
	if (!ft_strncmp(str, "-", ft_getmax_ln(str, "-")))
	{
		free(s);
		s = ft_strdup(g_ms->sh_env[opwd] + 7);
		ft_putstr_fd(s, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		free(s);
		s = ft_strdup(str);
	}
	ft_updt_err(0);
	return (s);
}

void	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	ft_updt_err(1);
}

int	ft_envfind(char *name)
{
	int		x;
	char	*tmp;

	x = -1;
	tmp = ft_strjoin(name, "=");
	while (g_ms->sh_env[++x])
	{
		if (!ft_strncmp(g_ms->sh_env[x], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (x);
		}
	}
	free(tmp);
	return (-1);
}

void	cd_env(int i[2])
{
	char	*new_oldpwd;
	char	*tmp;

	new_oldpwd = ft_strdup(g_ms->sh_env[i[0]] + 4);
	free(g_ms->sh_env[i[0]]);
	tmp = getcwd(NULL, 0);
	g_ms->sh_env[i[0]] = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (i[1] == -1)
		ft_add_envglob(ft_strdup("OLDPWD"), new_oldpwd, 1);
	else
	{
		free(g_ms->sh_env[i[1]]);
		g_ms->sh_env[i[1]] = ft_strjoin("OLDPWD=", new_oldpwd);
		free(new_oldpwd);
	}
}
