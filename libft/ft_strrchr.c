/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:48:45 by eimaz-va          #+#    #+#             */
/*   Updated: 2019/11/25 21:39:29 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*aux;

	aux = NULL;
	if (!s)
	{
		while (s)
			s++;
		s++;
	}
	while (s)
	{
		if (*s == c)
			aux = (char *)s;
		if (!*s)
			return (aux);
		s++;
	}
	return (aux);
}
