/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:27:10 by eimaz-va          #+#    #+#             */
/*   Updated: 2019/11/21 12:57:35 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if (!str && c == '\0')
	{
		while (str)
			str++;
		str++;
	}
	while (str)
	{
		if (*str == c)
			return ((char *)str);
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (NULL);
}
