/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:46:21 by irodrigo          #+#    #+#             */
/*   Updated: 2022/02/11 11:49:42 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dst, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ml;
	size_t		len;
	size_t		i;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	len = ft_strlen(&s1[i]);
	if (len)
		while (s1[i + len - 1] && ft_strchr(set, s1[i + len - 1]) != NULL)
			len--;
	ml = (char *)malloc(sizeof(char) * len + 1);
	if (!ml)
		return (NULL);
	ml = ft_strncpy(ml, (char *)&s1[i], len);
	ml[len] = '\0';
	return (ml);
}
