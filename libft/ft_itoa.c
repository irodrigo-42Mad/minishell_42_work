/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:15:13 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/25 13:00:47 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnum_len(int n)
{
	size_t		i;

	i = 1;
	n /= 10;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			str_len;
	unsigned int	n_cpy;

	str_len = ft_strnum_len(n);
	n_cpy = n;
	if (n < 0)
	{
		n_cpy = -n;
		str_len++;
	}
	str = ft_calloc(str_len + 1, 1);
	if (!str)
		return (NULL);
	str[--str_len] = n_cpy % 10 + '0';
	n_cpy /= 10;
	while (n_cpy > 0)
	{
		str[--str_len] = n_cpy % 10 + '0';
		n_cpy /= 10;
	}
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}
