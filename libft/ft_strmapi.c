/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:36:11 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:36:13 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*nueva;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	nueva = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!nueva)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		nueva[i] = f(i, s[i]);
		i++;
	}
	nueva[i] = '\0';
	return (nueva);
}
