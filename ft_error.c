#include "minishell.h"

	// TODO Hacer que el elemento tome el error 
	// correspondiente dar un valor hay que llegar
	// a acuerdo respecto a valores err

	// TODO
	// actualizar valor de la var de err al final
	//
	//update_q_mark_variable(42);
void	ft_quote_err(int *sh_err)
{
	ft_msg(GN_MSG_02, 2);
	ft_msg_val(Q_ERR_01, *sh_err);
	*sh_err = 42;
}

void	ft_all_char_err(int *sh_err, char *str, int type)
{
	ft_msg(GN_MSG_02, 2);
	if (type == 1)
		ft_msg(T_ERR_01, 2);
	else if (type == 2)
		ft_msg(T_ERR_02, 2);
	ft_msg(str, 2);
	ft_msg("\'\n", 2);
	if (type == 1)
	{
		*sh_err = 258;
		//ft_updt_err(258);
	}
	else if (type == 2)
		*sh_err = 13;
}
