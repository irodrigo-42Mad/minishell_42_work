/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:22:45 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/06 17:10:50 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_redir(t_lst *lst)
{
	char	*st_aux;

	st_aux = lst->str_aux;
	while (lst->exe_state == SUCCESS && *st_aux != '\0')
	{
		if (*st_aux == '>' || *st_aux == '<')
		{
			if (*(st_aux + 1) == '>')
			{
				st_aux += 2;
				ft_redir(&st_aux, lst, FD_OUT, MULTIPLE);
			}
			else
			{
				if (*st_aux++ == '>')
					ft_redir(&st_aux, lst, FD_OUT, UNIQUE);
				else
					ft_redir(&st_aux, lst, FD_IN, UNIQUE);
			}
		}
		else
			st_aux++;
	}
}

char	*ft_obtain_file(t_lst *lst, char **str_line)
{
	char	*aux;
	char	*file;
	int		len;

	//len = string_length_bash(*str_line, SUCCESS);
	len = ft_set_lenv(*str_line, PARAM);
	//add_envar_len(&len, *str_line, PARAM);
	file = malloc(sizeof(char) * (len + 1));
	aux = file;
	ft_set_strandenv(&aux, str_line, lst, &len);
	//write_str_w_envar(str_line, &aux, &len, lst);
	return (file);
}

void	ft_redirections(t_ms *s)
{
	int		i;
	int		tot_proc;
	t_lst	*elm;

	i = 0;
	tot_proc = s->prcs_n;
	elm = s->instr;
	while (i++ < tot_proc)
	{
		if (elm->exe_state == SUCCESS)
		{
			ft_check_redir(elm);
			//ft_clean_hdoc_elm(elm);
			//redirection_checker(node);
			//clean_hdoc_bar(node);
		}
		elm = elm->next;
		//i++;
	}
}