/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:33:18 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/22 17:00:26 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nueva;
	int		len;
	int		i;
	int		j;

	i = -1;
	if (!s1)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2));
	nueva = malloc(sizeof(char) * (len + 1));
	if (!nueva)
		return (NULL);
	while (s1[++i] != '\0')
		nueva[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
	{
		nueva[i] = s2[j];
		i++;
		j++;
	}
	nueva[i] = '\0';
	return (nueva);
}
