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
	int		old_fd_list [2];
	t_lst *tmp;

	tmp = node;
	while (i > 0)
	{
		if(i != 1) //when its not the last process
			pipe(new_fd_list);
		g_ms->sh_pid = fork();
		if (g_ms->sh_pid == 0)
		{
			if(i != 1) 
				close(new_fd_list[0]);
			if (node->exe_state == SUCCESS)
				execute_child(node, new_fd_list, old_fd_list);
			else
				exit(0);
		}
		else
		{
//			ft_signal_main();
			handle_pipes(node,new_fd_list, old_fd_list);	//closes the necessary pipe fds
			close_all_fds(node);							//closes our fd in and out and reassing them to 0 and 1 if needed
		}
		node->node_pid = g_ms->sh_pid;
		node = node->next;									//rinse and repeat
		i--;
	}
	//probablemente close fds deberia ir aqui
	node = tmp;
	wait_childs();											//wait for execution to finish
}

void	handle_pipes(t_lst *node, int new_pip[2], int old_pip[2]) // change old_pipe to fd list
{
//	close(new_pip[1]);					//we close new pipe[1]
	if (node->el_nbr != 1)
		close(old_pip[0]);
	if (node->el_nbr != g_ms->prcs_n)
	{	//if last close new_pip[0] all new pipe is closed
		close(new_pip[1]);
		copy_pipe(new_pip, old_pip);
	}	//copy our pipe, note that even if we copy new_pipe[1] is always closed at this point. therefore old pipe[1] is always closed
}

void copy_pipe(int *pipe_in,int *pipe_out)
{
	pipe_out[0] = pipe_in[0];
	pipe_out[1] = pipe_in[1];
}


void	execute_child(t_lst *node, int new_fd_list[2], int old_fd_list[2])
{
	//handle_defs(node->str_args);							//just as in single proccess we handle definitions adding them to env list and erasing them from our cmd list
	open_heredoc(node);										//if here doc stdin set to it
	// this code fails assign_fd is faulty
	if (node->el_nbr != 1)									//if its NOT the first element
		assing_fd(&node->file_in, old_fd_list[0], FD_IN); 	//if fd_in is 0, we assing the read end of our old list else it closes old_fd[0]
	if (node->el_nbr != g_ms->prcs_n)						//if eits NOT the last
		assing_fd(&node->file_out, new_fd_list[1], FD_OUT); //if fd_in is 1, we assing the write end of our new_list else it closes new_fd[1]
//	else													//if last process we simply close the out fd of the new pipe
//		close(new_fd_list[1]);
	if (node->str_args[0])									//standart executing process
	{
		if (is_builtin(node->str_args[0]))
		{
			dup_to_stdin_stdout(node->file_in, node->file_out);
			exec_builtin(node->str_args, 0); //0 means child
		}
		else
			call_execve(node);
	}
}

void	wait_childs(void)
{
	int		state;
	t_lst *tmp;
	tmp = g_ms->instr;

	while (tmp)
	{
		state = 0; 
		waitpid(tmp->node_pid, &state, 0);				//wait for each process
//		printf("exit state is: %i\n",state);
//		printf("exit wexitstate is: %i\n",WEXITSTATUS(state));
		if (tmp->next == NULL)
			ft_get_errstatus(state);	// working in it
		tmp = tmp->next;
	}
//	printf("this is $?: %i\n", g_ms->err_n);
}
