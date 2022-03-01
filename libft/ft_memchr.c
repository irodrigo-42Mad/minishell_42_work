/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:54:41 by eimaz-va          #+#    #+#             */
/*   Updated: 2019/12/09 18:50:54 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*aux;

	aux = (unsigned char *)s;
	if (!n)
		return (NULL);
	if (!s && c == '\0')
	{
		while (s)
			s++;
		s++;
	}
	i = 0;
	while (i < n)
	{
		if (aux[i] == (unsigned char)c)
			return ((void *)&aux[i]);
		i++;
	}
	return (NULL);
}
