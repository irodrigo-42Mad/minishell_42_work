/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfile_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:29:44 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:36:39 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_rebuild_str(t_lst *lst)
{
	free(lst->str_aux);
	lst->str_aux = ft_strdup(lst->str_save);
	ft_mute_aux(lst->str_aux, lst->str_cmd);
	free(lst->str_aux_save);
	lst->str_aux_save = ft_strdup(lst->str_aux);
}

void	prepare_strline(t_lst	*aux)
{
	char	*tmp;

	tmp = trim(aux->str_line);
	free(aux->str_line);
	aux->str_line = tmp;
	aux->str_line = erase_redir(aux->str_line);
	tmp = expand_vars2(aux->str_line);
	free(aux->str_line);
	aux->str_line = tmp;
}

char	*add_space(char *s)
{
	int	i;
	int	com[2];

	i = -1;
	com[0] = 0;
	com[1] = 0;
	while (s[++i])
	{
		if ((s[i] == '\'') && (com[0] == 0))
			com[0] = 1;
		else if ((s[i] == '\"') && (com[1] == 0))
			com[1] = 1;
		else
			s = second_comma(s, i, com);
	}
	return (s);
}

char	*second_comma(char *s, int i, int *com)
{
	if ((s[i] == '\'') && (com[0] == 1))
	{
		if (((!(ft_isspace(s[i + 1])))) && (com[1] == 0))
			s = space_in(s, i + 1);
		com[0] = 0;
	}
	else if ((s[i] == '\"') && (com[1] == 1))
	{
		if (((!(ft_isspace(s[i + 1])))) && (com[0] == 0))
			s = space_in(s, i + 1);
		com[1] = 0;
	}
	return (s);
}

char	*space_in(char *s, int pos)
{
	int		i;
	int		y;
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(s) + 2));
	i = 0;
	y = 0;
	while (s[i])
	{
		if (i == pos)
			tmp[y++] = ' ';
		tmp[y] = s[i];
		y++;
		i++;
	}
	tmp[y] = '\0';
	free (s);
	return (tmp);
}
