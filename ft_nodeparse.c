#include "minishell.h"

t_lst	*ft_newinst()
{
	t_lst	*elm;

	elm = ft_calloc(1,sizeof(t_lst));
	elm->file_in = FD_IN;
	elm->file_out = FD_OUT;
	elm->exe_state = SUCCESS;
	//elm->ln = ft_strchlen(, '|');

	return (elm);
}


void	ft_prepare_command(t_ms *s)
{
	t_lst	*p_inst;
	t_lst	*aux;

	s->cmd = ft_strdup("hola");
	s->str = s->cmd;
	s->lastcmd = s->str;
	p_inst = ft_newinst();
	s->instr = p_inst;
	while (*s->str)
	{
		aux = ft_newinst();
		p_inst->next = aux;
	}
	free(s->cmd);
	free(s->str);


	// g_shell->parse_rl = g_shell->rl_tofree;
	// g_shell->rl_aux = g_shell->rl;
	// p_nd = create_pnode(&g_shell->parse_rl, &g_shell->rl_aux, &g_shell->n_proc);
	// g_shell->p_lst = p_nd;
	// while (*g_shell->parse_rl)
	// {
	// 	p_nd->next = create_pnode(&g_shell->parse_rl,
	// 			&g_shell->rl_aux, &g_shell->n_proc);
	// 	p_nd = p_nd->next;
	// }
	// free(g_shell->rl_tofree);
	// free(g_shell->rl);

}
