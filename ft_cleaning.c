#include "minishell.h"

void ft_pre_clean(t_ms *g_ms)
{
	if (g_ms->sh_env)
		free_matrix(g_ms->sh_env);
	if (g_ms->sh_envar)
	 	free_vars(g_ms->sh_envar);
	free(g_ms->prompt);
	g_ms->argc = 0;
	g_ms->state = 0;
	g_ms->flg_err = 0;
	if (g_ms->instr)
		free_nodes(g_ms->instr);
	ft_bzero(g_ms, sizeof(t_ms));
}
