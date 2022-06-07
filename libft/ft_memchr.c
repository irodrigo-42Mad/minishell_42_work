/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:34:17 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:34:20 by mgrau            ###   ########.fr       */
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
