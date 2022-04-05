/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:22:45 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/31 17:10:50 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlcpy(char *dst, const char *src, size_t begin, size_t len)
{
	size_t	i;
	size_t	pos;

	if (!dst || !src)
		return (0);
	if (len == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < (begin + 1))
		i++;
	pos = 0;
	while ((pos < (len - 1)) && src[i])
	{
		dst[pos] = src[i];
		i++;
		pos++;
	}
	dst[pos] = '\0';
	return (ft_strlen(src));
}
