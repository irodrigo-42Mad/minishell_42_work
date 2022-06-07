/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:35:46 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:35:48 by mgrau            ###   ########.fr       */
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
