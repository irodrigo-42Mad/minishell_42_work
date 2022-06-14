/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:54:51 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/14 08:35:47 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_heredoc(void)
{
	t_lst	*lst;
	char	*tmp;
	int		x;

	x = g_ms->prcs_n;
	lst = g_ms->instr;
	while (x-- > 0)
	{
		ft_set_hdoc(lst);
		ft_rebuild_str(lst);
		prep_strcmd(lst);
		lst = lst->next;
	}
	tmp = set_hdocfname(NOT_EXIST);
	free(tmp);
}

char	*set_hdocfname(int exist)
{
	static int	x;
	char		*f_name;
	char		*tmp;

	if (!x)
		x = 0;
	tmp = NULL;
	f_name = NULL;
	if (exist == 0)
		x = 0;
	else
	{
		tmp = ft_itoa(x);
		f_name = ft_strjoin(".here_doc", ft_itoa(x));
		free(tmp);
		x++;
	}
	return (f_name);
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

void	look_for_begin(char *tmp, int *begin, int *quotes)
{
	if ((*quotes) == 0)
	{
		d_comma(tmp[(*begin)], quotes);
		if ((*quotes) > 0)
			(*begin)++;
	}
	else
	{
		d_comma(tmp[(*begin)], quotes);
		if ((*quotes) == 0)
			(*begin)++;
	}
}
