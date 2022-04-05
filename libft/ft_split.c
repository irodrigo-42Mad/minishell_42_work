/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:35:12 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/22 17:06:25 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		words;
	int		hasword;

	i = 0;
	words = 0;
	hasword = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c && s[i])
			hasword = 1;
		if (s[i] == c)
		{
			while (s[i] == c && s[i])
				i++;
			if (s[i])
				words++;
		}
		else
			i++;
	}
	return (words + hasword);
}

static char	*ft_alloc_word(char const *s, char c)
{
	int		size;
	char	*tab;

	size = 0;
	tab = 0;
	while (s[size] && s[size] != c)
		size++;
	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s, size + 1);
	return (tab);
}

char	*equis(char **tab, int count)
{
	if (!tab[count])
	{
		while (count > 0)
			free(tab[count--]);
		free(tab);
		return (NULL);
	}
	return (*tab);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		words;
	char	**tab;

	count = -1;
	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	while (++count < words)
	{
		while (s[0] == c)
			s++;
		tab[count] = ft_alloc_word(s, c);
		equis(tab, count);
		s += ft_strlen(tab[count]);
	}
	tab[count] = 0;
	return (tab);
}
