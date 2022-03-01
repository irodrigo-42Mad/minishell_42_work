#include "../minishell.h"

/*
** notes at this function
**
** getcwd() allocates the buffer dynamically using malloc(3) if buf is NULL.
** In this case, the allocated buffer has the length size unless size is zero,
** when buf is allocated as big as necessary. The caller should free(3) the =
** returned buffer element.
**
*/

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	//qmark?
}
