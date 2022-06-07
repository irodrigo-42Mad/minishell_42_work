/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:33:49 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:33:52 by mgrau            ###   ########.fr       */
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
