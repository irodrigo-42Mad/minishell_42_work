/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:33:01 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:33:03 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lista;

	lista = *lst;
	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		while (lista->next)
			lista = lista->next;
		lista->next = new;
	}
}
