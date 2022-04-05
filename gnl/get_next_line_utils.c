/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:53:11 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/22 17:56:38 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*c;
	int		i;

	c = (char *)malloc(ft_strlen(s1) + 1);
	if (!c)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		c[i] = s1[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	if (!s1)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2));
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		new[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strchr(const char *s1, int c)
{
	if (!s1 && c == '\0')
	{
		while (s1)
			s1++;
		s1++;
	}
	while (s1)
	{
		if (*s1 == c)
			return ((char *)s1);
		if (*s1 == '\0')
			return (NULL);
		s1++;
	}
	return (NULL);
}
