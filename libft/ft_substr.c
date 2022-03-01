/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:03:47 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/21 23:11:14 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*nueva;
	size_t	i;

	nueva = malloc(sizeof(char) * len + 1);
	if (!nueva)
		return (NULL);
	if (!s || (ft_strlen(s) < start))
		return (ft_strdup(""));
	i = 0;
	if (ft_strlen(s) > start)
	{
		while (i < len)
		{
			nueva[i] = s[start + i];
			i++;
		}
		nueva[i] = '\0';
	}
	return (nueva);
}
