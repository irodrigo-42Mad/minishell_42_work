/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:51:47 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/21 18:15:15 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nlst;

	nlst = (t_list *)malloc(sizeof(t_list));
	if (!nlst)
		return (NULL);
	nlst->content = content;
	nlst->next = NULL;
	return (nlst);
}
