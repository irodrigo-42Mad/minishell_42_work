/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 20:44:58 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/21 18:11:38 by eimaz-va         ###   ########.fr       */
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
