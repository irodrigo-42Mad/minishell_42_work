#include "minishell.h"

void	dup_to_stdin_stdout(int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
		if (dup2(fd_in, 0) == -1)
			printf("error in dup2");//error_message();
		close(fd_in);
	}
	if (fd_out != 1)
	{
		if (dup2(fd_out, 1) == -1)
			printf("error in dup2");//error_message();
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
