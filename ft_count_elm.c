#include "minishell.h"

int	ft_count_orders(void)
{
	size_t	pos;

	pos = 0;
	while (g_ms->str[pos] != '\0')
	{
		if (g_ms->str[pos] == '|')
		{
			if (g_ms->str[pos + 1] == '|')
				return (1);
			else
				g_ms->pip_count++;
		}
		pos++;
	}
	return (0);
}


void	ft_lstcmdadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*lista;

	lista = *lst;
	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		while (lista->next)
			lista = lista->next;
		lista->next = new;
	}
}
