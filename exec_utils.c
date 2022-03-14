/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:48:46 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/14 14:55:32 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//hdoc_name not yet set

/*
** notes to open_heredoc
**
** //if we have a heredoc we open it and asing our file in to it
** Function Variables:
**
**    herename location where our heredoc name is stored
**
**    when herename is present,
**    //we open and assing it as our file in (node->file_in)
*/
void	open_heredoc(t_lst *node)
{
	char	*path;

	path = NULL;
	if (!node->herename)
		return ;
	else
	{
		path = ft_strjoin(TMP_PATH, node->herename);
		node->file_in = open(path, O_RDONLY);
		free(path);
	}
}

/*
** notes for char	**str_ptr_dup(char **src)
** duplicating char** matrix
*/
char	**str_ptr_dup(char **src)
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

/*
** notes for size_t	ft_matrixlen(char **matrix)
**   for finding out the lenght of a char ** matrix
*/
size_t	ft_matrixlen(char **matrix)
{
	size_t	len;

	len = 0;
	if (!matrix)
		return (0);
	while (matrix[len])
		len++;
	return (len);
}

/*
** function creating for freeing matrixes
*/
void	free_matrix(char **matrix)
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

size_t	ft_maxlen(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
}
