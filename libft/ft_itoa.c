/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:09:30 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/22 17:42:05 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int c)
{
	int	len;

	len = 0;
	while (c / 10)
	{
		c /= 10;
		len++;
	}
	len++;
	return (len);
}

int	ft_negative(int n, unsigned int tmp)
{
	if (n < 0)
		tmp = -n;
	else
		tmp = n;
	return (tmp);
}

int	ft_flag(int n, int flag)
{
	if (n < 0)
		flag = 1;
	else
		flag = 0;
	return (flag);
}

char	*ft_itoa(int n)
{
	char			*nueva;
	unsigned int	tmp;
	int				i;
	int				flag;

	i = 0;
	flag = 0;
	tmp = 0;
	flag = ft_flag(n, flag);
	tmp = ft_negative(n, tmp);
	i = ft_count(tmp);
	nueva = malloc(sizeof(char) * i + 1 + flag);
	if (!nueva)
		return (NULL);
	nueva[i + flag] = '\0';
	while (--i > 0)
	{
		nueva[i + flag] = ((tmp % 10) + '0');
		tmp = tmp / 10;
	}
	nueva[i + flag] = ((tmp % 10) + '0');
	if (flag == 1)
		nueva[0] = '-';
	return (nueva);
}
