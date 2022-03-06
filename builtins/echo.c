#include "../minishell.h"

/* The value for a variable only visible thourgh export with no
 * arguments (declare -x name_of_variable) is a '\\'. Luckily,
 * no extern '\\' can be found in this shell except for the ones
 * I manually put, so I can just skip them when printing a string
 * and everyones happy. You didnt see anthing. */
void	ft_putstr_fd_without_esc_bar(char *str, int fd)
{
	while (*str)
	{
		if (*str != '\\')
			write(fd, str, 1);
		str++;
	}
}

void	ft_echo(char **arg)
{
	int	i;
	int	newline;

	newline = 1;
	i = 0;
	if (!arg[1])
	{
		ft_putstr_fd("\0", 1);
		ft_putstr_fd("\n", 1);
		ft_updt_err(0);
		//update qmark?
		return ;
	}
	while (arg[++i] && !ft_strncmp(arg[i], "-n", ft_getmax_ln(arg[i], "-n")))
		newline = 0;
	while (arg[i])
	{
		ft_putstr_fd_without_esc_bar(arg[i++], FD_OUT);
		if (arg[i])
			ft_putstr_fd(" ", FD_OUT);
	}
	if (newline == 1)
		ft_putstr_fd("\n", FD_OUT);
	ft_updt_err(0);
	//update_q_mark_variable(0);
}
