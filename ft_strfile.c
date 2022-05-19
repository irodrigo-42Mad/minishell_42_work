/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:32:42 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/19 14:19:46 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_str(char *str, t_lst *lst)
{
	int	ln;
	int	pos;
	int	flg;

	ln = (int)(ft_strlen(lst->str_save) - ft_strlen(str));
	pos = -1;
	flg = 0;
	while (++pos <= ln)
	{
		if (flg == 0 && lst->str_save[pos] == '<')
			if (lst->str_save[pos + 1] == '<')
				flg = 1;
		if (flg == 1)
			lst->str_save[pos] = ' ';
	}
	lst->str_save[pos] = '\\';
	if (lst->str_save[pos + 1] == '\"')
		lst->str_save[pos + 1] = ' ';
}

void	ft_mute_aux(char *str, char *str2)
{
	size_t	pos;
	size_t	ln;
	int		flg;

	flg = 0;
	pos = 0;
	ln = ft_strlen(str);
	while (ln-- > 0 && str[pos] != '\0')
	{
		if ((str[pos] == '\"') && flg == 0)
			add_flag(&pos, &flg, 1);
		if ((str[pos] == '\'') && flg == 0)
			add_flag(&pos, &flg, 2);
		if (flg > 0)
		{
			str[pos] = str2[pos];
			if (str[pos] == '\"' && flg == 1)
				flg = 0;
			if (str[pos] == '\'' && flg == 2)
				flg = 0;
		}
		pos++;
	}
}

char	*trim(char *s)
{
	int		i;
	int		y;
	char	*tmp;
	char	*dest;

	i = 0;
	y = 0;
	tmp = malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[i])
	{
		while (isspace(s[i]) && s[i])
			i++;
		while ((!(isspace(s[i]))) && s[i])
		{
			tmp[y] = s[i];
			i++;
			y++;
		}
		tmp[y++] = s[i];
	}
	dest = ft_strdup(tmp);
	free(tmp);
	return (dest);
}

void	ft_restore_str_command(void)
{
	t_lst	*aux;

	aux = g_ms->instr;
	while (aux)
	{
		aux->str_cmd = add_space(aux->str_cmd);
		aux->str_args = ft_split(ft_prepare_aux(aux->str_cmd), '|');
		prepare_strline(aux);
		reconstruction(aux);
		aux = aux->next;
	}
}

void	reconstruction(t_lst *aux)
{
	char	*element;
	int		i_pr;
	int		len;
	int		pos;

	pos = 0;
	i_pr = -1;
	while (aux->str_args[++i_pr])
	{
		len = ft_strlen(aux->str_args[i_pr]);
		element = (char *) malloc (sizeof(char) * (len + 1));
		ft_strnlcpy(element, aux->str_line, pos - 1, len + 1);
		if (precise_cmp(aux->str_args[i_pr], element, len))
			pos += ++len;
		else
		{
			ft_strnlcpy(aux->str_args[i_pr], element, -1, len + 1);
			pos += ++len;
		}
		aux->str_args[i_pr] = expand_vars(aux->str_args[i_pr]);
		free (element);
	}
}
