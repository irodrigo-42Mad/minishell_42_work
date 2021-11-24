#include "libft.h"

int	ft_isalltab(int c)
{
	if (c >= 9 && c <= 13)
		return (1);
	else
		return (0);
}
