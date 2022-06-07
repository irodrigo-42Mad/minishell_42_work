/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:36:42 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:36:44 by mgrau            ###   ########.fr       */
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
	{
		free(nueva);
		return (ft_strdup(""));
	}
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
