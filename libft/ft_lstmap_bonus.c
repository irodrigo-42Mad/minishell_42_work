/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:38:24 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/21 18:13:46 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lista;
	t_list	*cpy;
	t_list	*nx;

	if (lst && f)
	{
		nx = ft_lstnew(lst->content);
		lista = nx;
		lista->content = f(lista->content);
		if (!lista->content)
			del(lista->content);
		while (lst->next != NULL)
		{
			lst = lst->next;
			cpy = ft_lstnew(lst->content);
			cpy->content = f(cpy->content);
			if (!cpy->content)
				del(cpy->content);
			nx->next = cpy;
			nx = cpy;
		}
		return (lista);
	}
	return (0);
}
