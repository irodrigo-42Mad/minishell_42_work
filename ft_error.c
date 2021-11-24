#include "minishell.h"

	// TODO Hacer que el elemento tome el error 
	// correspondiente dar un valor hay que llegar
	// a acuerdo respecto a valores err

	// TODO
	// actualizar valor de la var de err al final
	//
	//update_q_mark_variable(42);
void	ft_quote_err(int *q_err)
{
	ft_msg(GN_MSG_02, 2);
	ft_msg_val(Q_ERR_01, *q_err);
	*q_err = 42;
}
