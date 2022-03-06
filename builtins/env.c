#include "../minishell.h"

void	ft_env(void)
{
	int		i;
	char	*name;

	i = 0;
	ft_updt_err(0); //update_q_mark_variable(0);
	while (g_ms->sh_env[i])
	{
		name = ft_getname(g_ms->sh_env[i]);
		//name = get_var_name(g_ms->sh_env[i]);
		if (*(g_ms->sh_env[i] + ft_strlen(name) + 1) != '\\')
			printf("%s\n", g_ms->sh_env[i]);
		free(name);
		i++;
	}
}
