/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_auxfn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:06:30 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/16 09:13:08 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** function creating for freeing matrixes
*/	
void	free_matrix(char **matrix)
{
	int	i;
	int	ln;

	i = 0;
	if (!matrix)
		return ;
	else
	{
		while (matrix[i])
		{
			ln = 0;
			while (matrix[i][ln])
			{
				matrix[i][ln] = '\0';
				ln++;
			}
			free(matrix[i]);
			i++;
		}
		free(matrix);
		matrix = NULL;
	}
}

void	free_vars(t_sh_var *elm)
{
	t_sh_var	*aux;

	if (!elm)
		return ;
	else
	{
		aux = elm;
		while (aux)
		{
			ft_bzero(elm->v_name, ft_strlen(elm->v_name));
			ft_bzero(elm->v_val, ft_strlen(elm->v_val));
			free(elm->v_name);
			free(elm->v_val);
			aux = elm->next;
			elm->next = NULL;
			free(elm);
			elm = NULL;
		}
		free(aux);
		aux = NULL;
	}
}

void	free_nodes(t_lst *elm)
{
	t_lst	*aux;
	t_lst	*act;

	if (!elm)
		return ;
	else
	{
		aux = elm;
		act = aux;
		while (act)
		{
			act = aux;
			node_to_zero(aux);
			aux->next = NULL;
			free(aux);
			aux = NULL;
		}
		free(elm);
		elm = NULL;
	}
}

void	node_to_zero(t_lst *aux)
{
	if (!aux->herename)
		ft_bzero(aux->herename, ft_strlen(aux->herename));
	if (!aux->str_cmd)
		ft_bzero(aux->str_cmd, ft_strlen(aux->str_cmd));
	if (!aux->str_line)
		ft_bzero(aux->str_line, ft_strlen(aux->str_line));
	if (!aux->str_aux)
		ft_bzero(aux->str_aux, ft_strlen(aux->str_aux));
	if (!aux->str_save)
		ft_bzero(aux->str_save, ft_strlen(aux->str_save));
	if (!aux->str_aux_save)
		ft_bzero(aux->str_aux_save, ft_strlen(aux->str_aux_save));
}
