
#include "minishell.h"
#include <sys/wait.h>


void	launch_several_process(t_lst *node, int i)
{
	int		new_fd_list[2];
	int		*old_fd_list;

	old_fd_list = NULL;
	while (i > 0)								//while number of processes
	{
		pipe(new_fd_list);						//we create a pipe
		g_ms->sh_pid = fork();
		if (g_ms->sh_pid == 0)  				// we are in child
		{
			close(new_fd_list[0]);				//close pipefd[0], the read end of the pipe
			if (node->exe_state == SUCCESS)
				execute_child(node, new_fd_list, old_fd_list);
			else
				exit(0);
		}
		else			//we are in father
		{
//			ft_signal_main();
			handle_pipes(node,new_fd_list, old_fd_list);	//closes the necessary pipe fds
			close_all_fds(node);							//closes our fd in and out and reassing them to 0 and 1 if needed
		}
		node = node->next;									//rinse and repeat
		i--;
	}
	wait_childs();											//wait for execution to finish
}

void	handle_pipes(t_lst *node, int new_pip[2], int old_pip[2]) // change old_pipe to fd list
{
	close(new_pip[1]);					//we close new pipe[1]
	if (node->el_nbr != 1)				//if NOT the first close old_pipe[0]
	{
		close((old_pip)[0]);
		free(old_pip);
	}
	if (node->el_nbr == g_ms->prcs_n)	//if last close new_pip[0] all new pipe is closed
		close(new_pip[0]);
	else
		old_pip = copy_pipe(new_pip);	//copy our pipe, note that even if we copy new_pipe[1] is always closed at this point. therefore old pipe[1] is always closed
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
	handle_defs(node->cmd);									//just as in single proccess we handle definitions adding them to env list and erasing them from our cmd list
	open_heredoc(node);										//if here doc stdin set to it
	if (node->el_nbr != 1)									//if its NOT the first element
		assing_fd(&node->file_in, old_fd_list[0], FD_IN); 	//if fd_in is 0, we assing the read end of our old list else it closes old_fd[0]
	if (node->el_nbr != g_ms->prcs_n)						//if eits NOT the last
		assing_fd(&node->file_out, new_fd_list[1], FD_OUT); //if fd_in is 1, we assing the write end of our new_list else it closes new_fd[1]
	else													//if last process we simply close the out fd of the new pipe
		close(new_fd_list[1]);
	if (node->cmd[0])										//standart executing process
	{
		if (is_builtin(node->cmd[0]))
		{
			dup_to_stdin_stdout(node->file_in, node->file_out);
			exec_builtin(node->cmd, 0); //0 means child
		}
		else
			call_execve(node);
	}
}

void	wait_childs(void)
{
	int		n_process;
	int		stat;
	pid_t	pid;

	n_process = g_ms->prcs_n;
	while (n_process > 0)
	{
		pid = wait(&stat);				//wait for each process
//		if (pid == g_ms->sh_pid)
//			get_q_mark(stat);			//not yet set
		n_process--;
	}
}