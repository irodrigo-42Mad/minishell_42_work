#include "../minishell.h"
void	ft_exit(char **args, int call)
{
	int		is_num;

	if (call == 1) //1 means father
		ft_putstr_fd("exit\n", 2);
	if (!args[1])
		exit(0);
	is_num = check_if_digit(args[1]);
	if (!is_num)
	{
		exit_error(args[1], 0);
		exit(255);
	}
	else
	{
		if (!args[2])
			exit(ft_atoi(args[1]));
		else
			exit_error(args[1], 1);
	}
}

int	check_if_digit(const char *str)
{
	int is_num;
	size_t	i;

	is_num = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && is_num)
		if (!ft_isdigit(str[i++]))
			is_num = 0;
	return (is_num && i > 0);
}
