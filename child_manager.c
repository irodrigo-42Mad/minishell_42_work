/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:48:20 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/14 15:06:50 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/*
** notes for launch_several_process
**
** variables
**		i		int type
**	this variable controls number of process
**	while exist process do (i check)
**
**	pipe instruction was used to create pipe streams
**	take the element sh_pid with fokr order
**		if sh_pid is 0 we are in child process
**			in this moment close fd[0], the read end of the pipe
**		in other case we arein father
**			need to control signals ft_signal_main
**			close necesary pipes
**			close FD and reasign elements
**
**		rinse and repeat
**		wait for execution to finish
*/

void	launch_several_process(t_lst *node, int i)
{
	int		new_fd_list[2];
	int		*old_fd_list;

	old_fd_list = NULL;
	while (i > 0)
	{
		pipe(new_fd_list);
		g_ms->sh_pid = fork();
		if (g_ms->sh_pid == 0)
		{
			close(new_fd_list[0]);
			if (node->exe_state == SUCCESS)
				execute_child(node, new_fd_list, old_fd_list);
			else
				exit(0);
		}
		else
		{
//			ft_signal_main();
			handle_pipes(node, new_fd_list, old_fd_list);
			close_all_fds(node);
		}
		node = node->next;
		i--;
	}
	wait_childs();
}

void	handle_pipes(t_lst *node, int new_pip[2], int old_pip[2])
{
	close(new_pip[1]);
	if (node->el_nbr != 1)
	{
		close((old_pip)[0]);
		free(old_pip);
	}
	if (node->el_nbr == g_ms->prcs_n)
		close(new_pip[0]);
	else
		old_pip = copy_pipe(new_pip);
}

int	*copy_pipe(int pipe_in[2])
{
	int	*pipe_out;

	pipe_out = malloc(sizeof(int) * 2);
	pipe_out[0] = pipe_in[0];
	pipe_out[1] = pipe_in[1];
	return (pipe_out);
}

void	execute_child(t_lst *node, int new_fd_list[2], int old_fd_list[2])
{
	handle_defs(&node->str_cmd);
	open_heredoc(node);
	// this code fails assign_fd is faulty
	if (node->el_nbr != 1)
		assing_fd(&node->file_in, old_fd_list[0], FD_IN);
	if (node->el_nbr != g_ms->prcs_n)
		assing_fd(&node->file_out, new_fd_list[1], FD_OUT);
	else
		close(new_fd_list[1]);
	if (node->str_cmd[0])
	{
		if (is_builtin(&node->str_cmd[0]))
		{
			dup_to_stdin_stdout(node->file_in, node->file_out);
			exec_builtin(&node->str_cmd, 0);
		}
		else
			call_execve(node);
	}
}

void	wait_childs(void)
{
	int		n_process;
	int		state;
	pid_t	pid;

	n_process = (g_ms->prcs_n + 1);
	while (--n_process > 0)
	{
		pid = wait(&state);
		if (pid == g_ms->sh_pid)
			ft_get_errstatus(state);
		//n_process--;
	}
}
