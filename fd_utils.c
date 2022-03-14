/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:49:11 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/14 15:08:56 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assing_fd(int *node_fd, int new_fd, int fd)
{
	if (*node_fd == fd)
		*node_fd = new_fd;
	else
		close(new_fd);
}

void	dup_to_stdin_stdout(int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
		if (dup2(fd_in, 0) == -1)
			ft_msg(T_ERR_05, 2);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		if (dup2(fd_out, 1) == -1)
			ft_msg(T_ERR_05, 2);
		close(fd_out);
	}
}

void	close_all_fds(t_lst *node)
{
	if (node->file_in != 0)
	{
		close(node->file_in);
		node->file_in = 0;
	}
	if (node->file_out != 1)
	{
		close(node->file_out);
		node->file_out = 1;
	}
}
