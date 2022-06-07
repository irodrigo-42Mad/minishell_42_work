/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:35:52 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:35:54 by mgrau            ###   ########.fr       */
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
