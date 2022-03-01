#include "minishell.h"

void	start_executer(void)
{
	int		i;
	t_lst	*node;

	g_ms->state = EXECUTING;
	i = g_ms->prcs_n;
	node = g_ms->instr; 					//the start of our node linked list
	if (i == 1) 							//depending on the number of processes to execute we need to handle them differently
		launch_single_process(node);
	else
		launch_several_process(node, i);
	g_ms->sh_pid = 0;
	g_ms->state = READING;
}

void	launch_single_process(t_lst *node)
{
	if (node->exe_state == SUCCESS)
	{
		handle_defs(&node->str_cmd); 		//handle defs checks if the arguments are definitions, adds them and removes them from our cmd list in this node
		open_heredoc(node);					//open heredoc checks if there is a heredoc name and opens it
		if (node->str_cmd[0])				//if there is an argument
		{
			if (is_builtin(&node->str_cmd[0]))	//is it a built in?
				launch_from_father(node);		//if it is will launch from father
			else
				launch_from_fork(node);		//if not we must fork just like in several process route
		}
	}
}

void	launch_from_father(t_lst *node)
{
	int		stdin_fd;
	int		stdout_fd;

	stdin_fd = dup(0);
	stdout_fd = dup(1); 								// since we are lauching from father we create a back up for the original stdin and stdout
	dup_to_stdin_stdout(node->file_in, node->file_out); //we asing the new stdin stdout if any chages apply
	exec_builtin(&node->str_cmd, 1); 					//1 means father, we exec our built in
	dup_to_stdin_stdout(stdin_fd, stdout_fd); 			//we close and restore original stdin stdout if needed
}

void	launch_from_fork(t_lst *node)
{
	g_ms->sh_pid = fork();				//we fork
	if (g_ms->sh_pid == 0)				//if we are in child we go to execution
		call_execve(node);
	else								//if we are in father
	{
//		ft_signal_main();				//signal
		close_all_fds(node);			//we close our fds
		wait_childs();					//we wait for the child to finish execution
		g_ms->state = READING;			//set state as reading again
	}
}

void	call_execve(t_lst *node)
{
	char	*path;
	char	**env;

//	ft_signal_main();										//signal
	dup_to_stdin_stdout(node->file_in, node->file_out);		//we set our stdin and stdout appropiately
	path = get_pathname(node->str_cmd);						//get our cmd path for execution
	env = str_ptr_dup(g_ms->sh_env);						// clone our env list for the execution
	if (execve(path, &node->str_cmd, env) == -1)
		printf("error in execve");//error_message(); we need to change all the prinf with our error function
}
///*************////
