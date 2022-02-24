#ifndef EXECUTER_H
# define EXECUTER_H
# include <fcntl.h>

#include <stddef.h>
///		executer.c
void	start_executer(void);
void	launch_single_process(t_lst *node);
void	launch_from_father(t_lst *node);
void	launch_from_fork(t_lst *node);
void	call_execve(t_lst *node);

///		builtin_utils.c
int		is_builtin(char *arg);
void	exec_builtin(char **arg, int type);
int 	precise_cmp(char *s1,char *s2, int size);

///		exec_utils.c
void	open_heredoc(t_lst *node);
char	**str_ptr_dup(char **src);
size_t	ft_matrixlen(char **matrix);
void	free_matrix(char **matrix);

///		fd_utils
void	dup_to_stdin_stdout(int fd_in, int fd_out);
void	close_all_fds(t_lst *node);
void	assing_fd(int *node_fd, int new_fd, int fd);

///		env_defs.c
void	handle_defs(char **cmd);
int		is_def(char *str);
char	*def_name(char *str);
void	add_def(char *name, char *value);
char 	**clear_cmd(char **cmd);

///		env_addition.c
char	*prev_env_value(char *name);
void	add_value_env(char *name, char *value);
t_var	*new_env_var(char *name, char *value);
void	overwrite_env_value(char *name, char *value);

///		child_management.c
void	launch_several_process(t_lst *node, int i);
void	handle_pipes(t_lst *node, int new_pip[2], int old_pip[2]);
int		*copy_pipe(int pipe_in[2]);
void	execute_child(t_lst *node, int new_fd_list[2], int old_fd_list[2]);
void	wait_childs(void);
#endif