#include "minishell.h"

	// TODO revisar a ver si en alguna ocasion necesitamos
	// devolver el valor de la longitud de la cadena y otros
	// elementos se puede usar ft_putstr_fd
void	ft_msg(char *str, int output)
{
	ft_putstr_fd(str, output);
}

int	ft_msg_val(char *str, int err_val)
{
	write (2, str, ft_strlen(str));
	return (err_val);
}
