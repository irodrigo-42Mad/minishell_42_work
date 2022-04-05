/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 08:21:01 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/21 18:12:14 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lista;
	t_list	*delete;

	lista = *lst;
	if (!lista)
		return ;
	while (lista)
	{
		delete = lista->next;
		del(lista->content);
		free(lista);
		lista = delete;
	}
	*lst = NULL;
}
