#include "minishell.h"

//hdoc_name not yet set

void	open_heredoc(t_lst *node) 					//if we have a heredoc we open it and asing our file in to it
{
	char	*path;

	path = NULL;
	if (!node->herename) 							// herename location where our heredoc name is stored
		return ;
	else
	{
		path = ft_strjoin(TMP_PATH, node->herename);
		node->file_in = open(path, O_RDONLY);		//we open and assing it as our file in
		free(path);
	}
}

char	**str_ptr_dup(char **src)				//for duplicating char** matrix
{
	char	**dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

size_t	ft_matrixlen(char **matrix)  			//for finding out the lenght of a char ** matrix
{
	size_t	len;

	len = 0;
	if (!matrix)
		return (0);
	while (matrix[len])
		len++;
	return (len);
}

void	free_matrix(char **matrix) 				// for freeing matrixes
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	else
	{
		while (matrix[i])
			free(matrix[i++]);
		free(matrix[i]);
		free(matrix);
	}
}
