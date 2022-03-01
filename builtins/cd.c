#include "../minishell.h"

void	ft_cd(char *str)
{
	char	*s;
	int		i[2];

	update_q_mark_variable(0);
	if ((i[0] = find_env("PWD")) == -1)
		add_to_global_env(ft_strdup("PWD"), getcwd(NULL, 0), 1);
	i[1] = find_env("OLDPWD");
	s = check_pwd(str, i[1], find_env("HOME"));
	if (chdir(s) == -1)
		cd_error(s);
	else
	{
		cd_env(i);
		update_q_mark_variable(0);
	}
	free(s);
}

char	*check_pwd(char *str, int opwd, int home)
{
	char	*s;

	s = NULL;
	s = str ? ft_strdup(str) : ft_strdup(g_ms->sh_env[home] + 5);
	if (!ft_strncmp(str, "-", ft_maxlen(str, "-")))
	{
		free(s);
		s = ft_strdup(g_ms->sh_env[opwd] + 7);
	}
	else
		s = ft_strdup(str);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	//update qmark?
	return (s);
}

void	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	//update_q_mark_variable(1);
}

void	cd_env(int i[2])
{
	char	*new_oldpwd;
	char	*pwd;
	char	*tmp;

	new_oldpwd = ft_strdup(g_ms->sh_env[i[0]] + 4);
	free(g_ms->sh_env[i[0]]);
	tmp = getcwd(NULL, 0);
	g_ms->sh_env[i[0]] = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (i[1] == -1)
		add_to_global_env(ft_strdup("OLDPWD"), new_oldpwd, 1);
	else
	{
		free(g_ms->sh_env[i[1]]);
		g_ms->sh_env[i[1]] = ft_strjoin("OLDPWD=", new_oldpwd);
		free(new_oldpwd);
	}
}
