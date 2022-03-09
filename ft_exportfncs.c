
#include "minishell.h"

void	ft_add_envglob(char *v_name, char *v_val, int status)
{
	if (status == UNDEF)
		ft_alreadydefined(v_name, v_val);
	else
		ft_envcreate(v_name, v_val);
}

/*
** this function check if env variable is already defined in
** system environment
*/

void	ft_alreadydefined(char *v_name, char *v_val)
{
	char	*tmp;
	int		existence;

	tmp = v_val;
	ft_chk_lval(v_name, &v_val);
	if (tmp != v_val)
		existence = SUCCESS;
	else
		existence = FAIL;
	if (existence != SUCCESS)
		ft_envcreate(v_name, v_val);
	else
		ft_recharge_env(v_name, v_val);
}

void	ft_envcreate(char *v_name, char *v_val)
{
	char	*tmp;
	char	**nenv;
	int		x;

	x = -1;
	nenv = malloc(sizeof(char *) * ((int)ft_matrixlen(g_ms->sh_env) + 2));
	// revisar si son necesarios los brackets
	while (g_ms->sh_env[++x])
		nenv[x] = ft_strdup(g_ms->sh_env[x]);
	tmp = ft_strjoin(v_name, "=");
	nenv[x++] = ft_strjoin(tmp, v_val);
	nenv[x] = NULL;
	free_ptrs(v_name, v_val, tmp);
	free_matrix(g_ms->sh_env);
	g_ms->sh_env = nenv;
}



/* There are two possibilities. If the value comes from the local
 * environment, then the environment matrix has to add a new entry
 * to it. If the value comes from the global env, then the
 * correspondent entry is the one that has to change, thus the size
 * of the matrix remains unchanged. */
void	ft_recharge_env(char *v_name, char *v_val)
 {
	char	*tmp;
	int		env_entry;

	env_entry = ft_envfind(v_name);
	tmp = NULL;
	if (env_entry == -1)
		ft_envcreate(v_name, v_val);
	else
	{
		tmp = ft_strjoin(v_name, "=");
		free(g_ms->sh_env[env_entry]);
		g_ms->sh_env[env_entry] = ft_strjoin(tmp, v_val);
		free_ptrs(v_name, v_val, tmp);
	}
 }
