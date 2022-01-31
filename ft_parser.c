#include "minishell.h"

int ft_parser (t_ms *s)
{
	char *straux;

	straux = s->str;
	while (*straux)
	{
		if (ft_isspace(*straux))
			*straux = ' ';
		straux++;
	}
	if (ft_quotes_threat(&s->str) || ft_redir_pipes(&s->err_n, &s->str))
	{
		free(s->cmd);
		free(s->str);
		return (1);
	}
	return (0);
}
