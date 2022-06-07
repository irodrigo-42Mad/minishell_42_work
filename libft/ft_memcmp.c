/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:34:24 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:34:27 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*t1;
	const unsigned char	*t2;
	size_t				i;

	t1 = s1;
	t2 = s2;
	i = 0;
	while (n != 0)
	{
		if (t1[i] != t2[i])
			return (t1[i] - t2[i]);
		n--;
		i++;
	}
	return (0);
}
