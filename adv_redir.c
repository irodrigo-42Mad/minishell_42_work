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

//tenemos que trabajar sobre las redirecciones a ver cual es el problema

//tenemos que trabajar en la forma en la que tomamos los elementos entre "" para funcionar


void	ft_check_redir(t_lst *lst)
{
	char	*st_aux;
	size_t	pos;

	pos = 0;
	//st_aux = lst->str_cmd;
	while (lst->exe_state == SUCCESS && lst->str_cmd[pos] != '\0')
	//while (lst->exe_state == SUCCESS && *st_aux != '\0')
	{
		if (lst->str_cmd[pos] == '>' || lst->str_cmd[pos] == '<')
		//if (*st_aux == '>' || *st_aux == '<')
		{
			if (lst->str_cmd[pos + 1] == '>')
			//if (*(st_aux + 1) == '>')
			{
				pos+= 2;
				st_aux = ft_calloc((ft_strlen(lst->str_cmd) - pos) + 1,
						 sizeof(char));
				ft_strnlcpy(st_aux, lst->str_cmd, pos,
					(ft_strlen(lst->str_cmd) - pos));
				//st_aux += 2;
				//ft_redir(,lst,FD_OUT, MULTIPLE);
				ft_redir(&st_aux, lst, FD_OUT, MULTIPLE);
			}
			else
			{
			 	if (lst->str_cmd[pos + 1] == '>')
				{
					pos++;
					st_aux = ft_calloc((ft_strlen(lst->str_cmd) - pos) + 1,
						 sizeof(char));
					ft_redir(&st_aux, lst, FD_OUT, UNIQUE);
				}
				else
				{
					size_t mlen;
					mlen = (ft_strlen(lst->str_cmd) - pos) + 1;
					st_aux = ft_calloc((ft_strlen(lst->str_cmd) - pos) + 1,
						 sizeof(char));
					ft_strnlcpy(st_aux, lst->str_cmd, pos,
						(ft_strlen(lst->str_cmd) - pos));
					ft_redir(&st_aux, lst, FD_OUT, UNIQUE);
				}
			// 	if (*st_aux++ == '>')
			// 		ft_redir(&st_aux, lst, FD_OUT, UNIQUE);
			// 	else
			// 		ft_redir(&st_aux, lst, FD_IN, UNIQUE);
			}
		}
		else
			pos++;
			//st_aux++;
	}
}
// revisar que tenemos que hacer con las redirecciones.

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

void	ft_redirections(void)
{
	int		i;
	int		tot_proc;
	t_lst	*elm;

	i = 0;
	tot_proc = g_ms->prcs_n;
	elm = g_ms->instr;
	//elm = s->instr;
	while (i++ < tot_proc)
	{
		if (elm->exe_state == SUCCESS)
		{
			if(elm->type == 1)
			{
				ft_check_redir(elm);
			//ft_clean_hdoc_elm(elm);
			//redirection_checker(node);
			//clean_hdoc_bar(node);
			}
		}
		elm = elm->next;
		// instr anterior (esto puede generar leaks de memoria)
	}
}
