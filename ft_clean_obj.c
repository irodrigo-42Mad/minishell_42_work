/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:45:04 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/08 15:22:18 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_clean_instr(t_lst *instr)
{
	t_lst *tmp;
	
	if (instr == NULL)
    	return ;
	tmp = instr;
	while (tmp->next != NULL)
	{
   		instr = tmp->next;
   		free (tmp);
   		tmp = instr;
	}
	free (tmp);
	instr = NULL;
}