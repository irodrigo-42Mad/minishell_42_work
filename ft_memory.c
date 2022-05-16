/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:48:48 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/16 09:31:57 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_two(void *s1, void *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

/*
void	ft_free_two(void *s1, void *s2)
{
	//size_t len;

	if (s1)
	{
		//len = ft_strlen(s1);
		//ft_bzero(s1, len);
		free(s1);
	}
	if (s2)
	{
		//len = ft_strlen(s2);
		//ft_bzero(s2, len);
		free(s2);
	}
}
*/
