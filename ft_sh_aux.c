

#include "minishell.h"


size_t	ft_max_ln(const char *str1, const char *str2)
{
	size_t len1;
	size_t len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}
