/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:22:45 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/20 10:38:08 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ft_clean_stredir(t_lst *lst, char *st_aux, size_t pos);

char	*get_filename(t_lst *lst, size_t *last_pos)
{
	size_t	end;
	size_t	begin;
	size_t	pos;
	char	*st_aux;

	pos = *last_pos;
	while (ft_isspace(lst->str_aux[pos]))
		pos++;
	if (lst->str_line[pos] == '\"' || lst->str_line[pos] == '\'')
	{
		begin = ++pos;
		if (lst->str_line[pos - 1] == '\'')
			end = ft_set_quote_pos(1, lst->str_aux, pos);
		else
			end = ft_set_quote_pos(2, lst->str_aux, pos);
	}
	else
	{
		begin = pos;
		end = ft_set_end(lst->str_aux, pos);
	}
	st_aux = (char *) malloc(sizeof(char) * (end + 1));
	ft_strnlcpy(st_aux, lst->str_aux, begin -1, (end + 1));
	*last_pos = pos;
	return (st_aux);
}

void	set_redirection(t_lst *lst, size_t *pos, int type)
{
	char	*st_aux;

	if (type == 1)
	{
		(*pos) += 2;
		st_aux = get_filename(lst, pos);
		ft_control_out_mode(st_aux, lst, APPEND);
	}
	else if (type == 2)
	{
		(*pos)++;
		st_aux = get_filename(lst, pos);
		ft_control_out_mode(st_aux, lst, TRUNCATE);
	}
	else
	{
		(*pos)++;
		st_aux = get_filename(lst, pos);
		ft_indirection(st_aux, lst);
	}
//	ft_clean_stredir(lst, st_aux, *pos);
	free(st_aux);
}

void	ft_check_redir(t_lst *lst)
{
	size_t	pos;

	pos = 0;
	while (lst->exe_state == SUCCESS && lst->str_aux[pos] != '\0')
	{
		if (lst->str_aux[pos] == '>')
		{
			if (lst->str_aux[pos + 1] == '>')
				set_redirection(lst, &pos, 1);
			else
				set_redirection(lst, &pos, 2);
		}
		else if (lst->str_aux[pos] == '<')
		{
			if (lst->str_aux[pos + 1] != '<')
				set_redirection(lst, &pos, 3);
		}
		else
			pos++;
	}
}

char	*ft_obtain_file(t_lst *lst, char **str_line)
{
	char	*aux;
	char	*file;
	int		len;

	len = ft_set_lenv(*str_line, PARAM);
	file = malloc(sizeof(char) * (len + 1));
	aux = file;
	ft_set_strandenv(&aux, str_line, lst, &len);
	return (file);
}

void	ft_redirections(void)
{
	int		i;
	t_lst	*elm;

	i = 0;
	elm = g_ms->instr;
	while (i++ < g_ms->prcs_n)
	{
		if (elm->exe_state == SUCCESS)
		{
			ft_check_redir(elm);
			ft_clean_hdoc_pos(elm);
		}
		elm = elm->next;
	}
}

void ft_clean_stredir(t_lst *lst, char *st_aux, size_t pos)
{
	size_t i;
	size_t len;


	//printf("st_aux: %s    pos %d\n\n\n", st_aux, pos);
	//printf ("line antes: %s\n", lst->str_line);
	//printf ("aux antes : %s\n", lst->str_aux);
	i = 0;
	len = (ft_strlen(st_aux) + pos);
	while (i < pos && !(lst->str_aux[i] == '>' || lst->str_aux[i] == '<'))
	{
	//while ((lst->str_aux[i] == ' ' || lst->str_aux[i] == '\\') && i < len)
		//if (lst->str_aux[i] == '>' || lst->str_aux[i] == '<')
		//	break ;
		i++;
	}
	//aqui me encuentro justo antes de la primera redireccion
	while (i < len)
	{
		if (lst->str_aux[i] == '>' || lst->str_aux[i] == '<')
		{
			lst->str_aux[i] = '\\';
			lst->str_line[i] = '\\';
		}
		else
		{
			lst->str_aux[i] = ' ';
			lst->str_line[i] = ' ';
		}
		i++;
	}
	//printf ("line despues: %s\n",lst->str_line);
	//printf ("aux despues : %s\n", lst->str_aux);
}
