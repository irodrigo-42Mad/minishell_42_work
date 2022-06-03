/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdoc_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:20:03 by mgrau             #+#    #+#             */
/*   Updated: 2022/06/03 08:48:05 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	ft_set_hdoc(t_lst *lst)
{
	char	*tmp;

	lst->str_aux = ft_strdup(lst->str_cmd);
	lst->str_save = ft_strdup(lst->str_line);
	tmp = lst->str_aux;
	while (*tmp != '\0')
	{
		tmp = ft_strnstr(tmp, "<<", ft_strlen(tmp));
		if (tmp == NULL)
			break ;
		else
		{
			tmp += 2;
			ft_set_strpntr(&tmp, &lst->str_aux, &lst->str_line, 2);
			ft_clear_str(tmp, lst);
		}
		lst->herename = ft_eofcatch(&lst->here_num, &lst->str_line);
		heredoc_opener(lst->herename);
	}
	if (lst->file_in != FD_IN)
		close(lst->file_in);
	lst->file_in = 0;
	ft_hdc_prepareln(lst);
}*/

void	ft_set_hdoc(t_lst *lst)
{
	char	*tmp;
	int		quotes;
	int		begin;
	int		len;
	lst->str_aux = ft_strdup(lst->str_cmd);
	lst->str_save = ft_strdup(lst->str_line);
	lst->str_aux_save = ft_strdup(lst->str_line);
	tmp = lst->str_save;
	quotes = 0;
	begin = 0;
	while (tmp[begin] != '\0')
	{
		begin = ft_strlen(lst->str_aux) - ft_strlen(ft_strnstr(tmp, "<<", ft_strlen(tmp)));
		if ((ft_strnstr(tmp, "<<", ft_strlen(tmp)) == NULL))
			break ;
		else
		{
			while (tmp[begin] == '<')
				begin++;
			while (ft_isspace(tmp[begin]))
				begin++;
			lst->herename = (char *) malloc(sizeof (char) * ((ft_strlen(tmp) - begin) + 1));
			len = 0;
			while (tmp[begin])
			{
				if (quotes == 0 && ft_isspace(tmp[begin]))
					break ;
				if (quotes == 0)
				{
					d_comma(tmp[begin], &quotes);
					if (quotes > 0)
						begin++;
				}
				else
				{
					d_comma(tmp[begin], &quotes);
					if (quotes == 0)
						begin++;
				}
				if (tmp[begin] != '\0')
				{
					lst->herename[len] = tmp[begin];
					begin++;
					len++;
				}
			}
			lst->herename[len] = '\0';
			// revisar aqui
			//ft_set_strpntr(&tmp, &lst->str_aux, &lst->str_line, 2);
			// hay que limpiar la cadena para quitar los elementos de heredoc que se han realizado
			//ft_clear_str(tmp, lst); // puede fallar aqui....
			lst->str_save = one_erase_redir(lst->str_save);
			lst->str_aux = one_erase_redir(lst->str_aux);
			tmp = lst->str_save;
		}
		//lst->herename = ft_eofcatch(&lst->here_num, &lst->str_line);
		heredoc_opener(lst->herename);
		//hacer free de herename
	}
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

void	ft_hdc_prepareln(t_lst *lst)
{
	int		pos;
	char	*tmp;

	pos = (lst->here_num + 1);
	tmp = lst->str_save;
	while ((--pos > 1) && *tmp != '\0')
	{
		tmp = ft_strnstr(tmp, "\\", ft_strlen(tmp));
		*tmp = ' ';
	}
	tmp = ft_strnstr(tmp, "\\", ft_strlen(tmp));
	if (tmp == NULL)
		return ;
	tmp++;
	while (*tmp == '*' && *tmp != '\0')
		*tmp++ = ' ';
	lst->str_line = lst->str_save;
}

int	heredoc_opener(char *file)
{
	char	*line;
	int		fd;

	fd = open(ft_strjoin(TMP_PATH, file), O_CREAT | O_WRONLY | O_TRUNC, 0666);
	g_ms->state = H_DOC_CMD;
	ft_set_signal();
	if ((fd < 0) || (!(g_ms->state == H_DOC_CMD)))
		return (-1);
	line = readline("> ");
	while ((line && !(precise_cmp(line, file, ft_strlen(file)))) \
	&& (g_ms->state == H_DOC_CMD))
	{
		if (!((file[0] == '\'') || (file[0] == '\"')))
			line = expand_vars(line);
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	free(line);
	close(fd);
	return (0);
}
/* signal main
  while (1)
  {
   line = readline("$> ");
   if (!line || !ft_strncmp(line, eof, ft_maxlen(line, eof)))
    exit(0);
   else
    write_line_on_hdoc(line, node->fdi);
  }*/
