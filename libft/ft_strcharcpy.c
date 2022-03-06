/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftrcharcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:18:28 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/04 13:05:19 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strcharcpy(char *dest, char *src, char until,
						unsigned int pos)
{
	unsigned int	i;

	i = 0;
	if ((!dest) || (!src))
		return (0);
	while ((src[pos] != '\0' && src[pos] != until))
		dest[i++] = src[pos++];
	dest[i] = 0;
	return (++pos);
}
