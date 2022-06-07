/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:33:14 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/07 11:33:18 by mgrau            ###   ########.fr       */
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
