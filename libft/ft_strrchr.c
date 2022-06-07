/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:36:34 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:36:36 by mgrau            ###   ########.fr       */
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
