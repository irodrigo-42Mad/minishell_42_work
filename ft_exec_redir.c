/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:46:12 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/08 09:45:36 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void	ft_redir(char **str, t_lst *lst, int dir, int mode)
{
	int		new_pos;
	char	*file;

	//ft_set_strbegin();

	//place_str_pointers(aux, &lst->line_aux, &lst->line, red);
	lst->str_line = ft_strdup(lst->str_cmd);
	file = ft_obtain_file(lst, &lst->str_line);
	if (lst->exe_state == SUCCESS)
	{
		if (mode == FD_OUT && dir == MULTIPLE)
			ft_control_mode(file, lst, APPEND);
		else if (mode == FD_OUT && dir == UNIQUE)
			ft_control_mode(file, lst, TRUNCATE);
		else
			ft_new_input(file, lst);
	}
	free(file);
	new_pos = lst->str_line - lst->str_save;
	new_pos -= (lst->str_aux - lst->str_aux_save);

	// ahi que mirar como movemos la position
	ft_locate_strptr(new_pos, &lst->str_aux, str);
	//move_str_pointers(new_pos, &lst->str_aux, str);
}

void	ft_control_mode(char *file, t_lst *lst, int mode)
{
	if (lst->file_out != 1)
			close(lst->file_out);
	if (mode == APPEND)
		lst->file_out = open(file, O_RDWR| O_APPEND | O_CREAT, 00644);
	else if (mode == TRUNCATE)
		lst->file_out = open(file, O_RDWR| O_TRUNC | O_CREAT, 00644);
	if (lst->file_out == -1)
		ft_write_file_err(lst, file);
}

void	ft_new_input (char *file, t_lst *lst)
{
	// temporal initialization

	int	fd = 0;

	//fd = check_for_hdoc_priority(lst->str_line);
	if (fd == -1)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			ft_write_file_err(lst, file);
		close(fd);
	}
	else
	{
		// tenemos que ver el tema de heredoc

		//if (node->hdoc_name)
		//	unlink_one_heredoc(&(node->hdoc_name));
		if (lst->file_in != 0)
			close(lst->file_in);
		lst->file_in = open(file, O_RDONLY);
		if (lst->file_in == -1)
			ft_write_file_err(lst, file);
	}
}
