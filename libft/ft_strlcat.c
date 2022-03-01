/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:05:18 by eimaz-va          #+#    #+#             */
/*   Updated: 2019/12/04 16:50:57 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	slen = ft_strlen(src);
	dlen = 0;
	while (dst[dlen] && dlen < dstsize)
		dlen++;
	i = dlen;
	while (src[dlen - i] && ((dlen + 1) < dstsize))
	{
		dst[dlen] = src[dlen - i];
		dlen++;
	}
	if (i < dstsize)
		dst[dlen] = '\0';
	return (i + slen);
}
