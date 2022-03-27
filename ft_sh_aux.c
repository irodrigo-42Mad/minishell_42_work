/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:41:41 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/07 15:13:22 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_getmax_ln(const char *str1, const char *str2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

void free_ptrs(char *one, char *two, char *three)
{
	if (one)
	{
		ft_bzero((void *)one, sizeof(one));
		free(one);
	}
	if (two)
	{
		ft_bzero((void *)two, sizeof(two));
		free(two);
	}
	if (three)
	{
		ft_bzero((void *)three, sizeof(three));
		free(three);
	}
}

int	ft_check_spc(char *str)
{
	int pos;
	int len;

	len = ft_strlen(str);
	pos = 0;
	while (ft_isspace(str[pos]) && str[pos] != '\0')
		pos++;
	if (pos >= len)
		return (1);
	else
		return (0);


}
