/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeparse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:19:27 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/03 09:42:54 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_newinst(char *cmd, int *i)
{
	t_lst		*elm;
	int			len;
	static int	begin;

	elm = ft_calloc (1, sizeof(t_lst));
	elm->el_nbr = (*i) + 1;
	elm->file_in = FD_IN;
	elm->file_out = FD_OUT;
	elm->exe_state = SUCCESS;
	elm->herename = NULL;
	elm->str_cmd = ft_strdup(cmd);
	len = ft_strlen(elm->str_cmd);
	if (*i == 0)
		begin = 0;
	elm->str_line = ft_substr(g_ms->str, begin, len);
	begin += len + 1;
	ft_bzero (cmd, sizeof(cmd));
	free(cmd);
	elm->next = NULL;
	return (elm);
}

void	ft_prepare_command(void)
{
	t_lst	*aux;
	char	**str;
	int		i;

	if (ft_count_orders() != 1)
	{
		i = 0;
		str = ft_split(g_ms->pars_cmd, '|');
		while (str[i] != NULL)
		{
			aux = ft_newinst(str[i], &i);
			ft_setlst_type(aux);
			ft_set_paramlst(aux);
			ft_lstcmdadd_back(&g_ms->instr, aux);
			g_ms->prcs_n++;
			i++;
		}
		free(str);
	}
	else
		return (ft_msg(Q_ERR_05, 2));
}

void	prep_strcmd(t_lst *aux)
{
	char	*s;

	s = expand_vars(aux->str_cmd);
	free(aux->str_cmd);
	aux->str_cmd = s;
}

void	ft_setlst_type(t_lst *aux)
{
	size_t	pos;
	size_t	len;

	pos = 0;
	len = ft_strlen (aux->str_cmd);
	while (pos < len && aux->type == 0)
	{
		if (aux->str_cmd[pos] == '\"')
			aux->type = 1;
		if (aux->str_cmd[pos] == '\'')
			aux->type = 2;
		if (aux->str_cmd[pos] == '>')
		{
			aux->type = 3;
			if (aux->str_cmd[pos + 1] == '>')
				aux->type = 4;
		}
		if (aux->str_cmd[pos] == '<')
		{
			aux->type = 5;
			if (aux->str_cmd[pos + 1] == '<')
				aux->type = 6;
		}
		pos++;
	}
}

void	ft_set_paramlst(t_lst *aux)
{
	size_t	pos;
	size_t	len;

	pos = 0;
	len = ft_strlen (aux->str_cmd);
	while (pos < len && aux->type == 0)
	{
		if (aux->str_cmd[pos] == '>' || aux->str_cmd[pos] == '<')
		{
			if (aux->str_cmd[pos + 1] == '<')
				aux->type = 3;
			if (aux->str_cmd[pos + 1] == '>')
				aux->type = 4;
		}
		else
		{
			aux->type = 1;
		}
		if (aux->str_cmd[pos] == '\"' || aux->str_cmd[pos] == '\'')
			aux->type = 2;
		pos++;
	}
}
