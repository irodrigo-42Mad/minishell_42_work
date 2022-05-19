/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:46:12 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/19 13:14:30 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h> 

int	ft_dircheck(char *file)
{
	DIR	*rst_dir;

	rst_dir = opendir(file);
	if (rst_dir)
	{
		closedir(rst_dir);
		return (ft_element_error(file, -126));
	}
	return (0);
}

void	ft_control_out_mode(char *file, t_lst *lst, int mode)
{
	if (lst->file_out != 1)
		close(lst->file_out);
	if (ft_dircheck(file) < 0)
		return ;
	if (mode == APPEND)
	{
		if (access(file, W_OK) != 0)
			lst->file_out = open(file, O_RDWR | O_APPEND);
		else
			lst->file_out = open(file, O_RDWR | O_CREAT, S_IRWXU);
	}
	else if (mode == TRUNCATE)
	{
		if (access(file, R_OK) != 0)
			unlink(file);
		lst->file_out = open(file, O_RDWR | O_CREAT, S_IRWXU);
	}
	if (lst->file_out == -1)
		ft_write_file_err(lst, file);
}

void	ft_indirection(char *file, t_lst *lst)
{
	if (!ft_dircheck(file))
	{
		if (access(file, R_OK) != 0)
			ft_write_file_err(lst, file);
		lst->file_in = open(file, O_RDONLY);
		if (lst->file_in == -1)
			ft_write_file_err(lst, file);
	}
}
