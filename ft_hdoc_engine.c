/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdoc_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:20:03 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/19 13:20:26 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (fd < 0)
		return (-1);
	write(1, "> ", 2);
	get_next_line(0, &line);
	while (!line || ft_strncmp(line, file, ft_strlen(file) != 0))
	{
		if (!((file[0] == '\'') || (file[0] == '\"')))
			line = expand_vars(line);
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
		line = NULL;
		write(1, "> ", 2);
		get_next_line(0, &line);
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
