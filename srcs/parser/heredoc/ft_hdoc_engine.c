/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdoc_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:20:03 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/14 08:35:41 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	hdoc_strings(t_lst *lst)
{
	lst->str_aux = ft_strdup(lst->str_cmd);
	lst->str_save = ft_strdup(lst->str_line);
	lst->str_aux_save = ft_strdup(lst->str_line);
}

void	ft_set_hdoc(t_lst *lst)
{
	char	*tmp;
	int		quotes;
	int		begin;

	hdoc_strings(lst);
	tmp = lst->str_save;
	quotes = 0;
	begin = 0;
	while (tmp[begin] != '\0')
	{
		begin = ft_strlen(lst->str_aux) - \
		ft_strlen(ft_strnstr(tmp, "<<", ft_strlen(tmp)));
		if ((ft_strnstr(tmp, "<<", ft_strlen(tmp)) == NULL))
			break ;
		else
		{
			hdoc_parse(lst, tmp, &begin, &quotes);
			tmp = lst->str_save;
		}
		heredoc_opener(lst->herename);
	}
}
	/*hacer free de herename*/

void	hdoc_parse(t_lst *lst, char *tmp, int *begin, int *quotes)
{
	while (tmp[(*begin)] == '<')
		(*begin)++;
	while (ft_isspace(tmp[(*begin)]))
		(*begin)++;
	lst->herename = (char *) malloc(sizeof (char) * \
	((ft_strlen(tmp) - (*begin)) + 1));
	get_herename(lst, tmp, begin, quotes);
	lst->str_save = one_erase_redir(lst->str_save);
	lst->str_aux = one_erase_redir(lst->str_aux);
}

void	get_herename(t_lst *lst, char *tmp, int *begin, int *quotes)
{
	int		len;

	len = 0;
	while (tmp[(*begin)])
	{
		if ((*quotes) == 0 && ft_isspace(tmp[(*begin)]))
			break ;
		look_for_begin(tmp, begin, quotes);
		if (tmp[(*begin)] != '\0')
		{
			lst->herename[len] = tmp[(*begin)];
			one_more2(begin, &len);
		}
	}
	lst->herename[len] = '\0';
}

char	*ft_eofcatch(int *hd_num, char **dat_line)
{
	char	*str;
	char	*tmp;
	char	*eof;
	int		ln;

	ln = (ft_str_bash_len(*dat_line, FAIL) + 1);
	tmp = malloc(sizeof(char) * ln);
	eof = tmp;
	str = *dat_line;
	ln--;
	while (ln > 0)
	{
		if (*str != '*')
		{
			*tmp++ = *str;
			ln--;
		}
		*str++ = ' ';
	}
	*tmp = '\0';
	*(--str) = '\\';
	*hd_num += 1;
	return (eof);
}
