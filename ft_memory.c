#include "minishell.h"


void	ft_free_two(void *s1, void *s2)
{
	size_t len;

	if (s1)
	{
		len = ft_strlen(s1);
		ft_bzero(s1, len);
		free(s1);
	}
	if (s2)
	{
		len = ft_strlen(s2);
		ft_bzero(s2, len);
		free(s2);
	}
}
