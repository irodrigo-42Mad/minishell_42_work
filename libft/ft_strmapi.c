/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:58:26 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/21 23:14:42 by eimaz-va         ###   ########.fr       */
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
