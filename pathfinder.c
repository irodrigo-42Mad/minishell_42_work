#include "minishell.h"

/*
**
** Notes to get_pathname
**
** checks if argument is valid and if it is returns the valid path for execution
**
*/

char	*get_pathname(char *arg)
{
	unsigned int	i = 5;
	char			*dest;
	char			*paths;

	if (access(arg, X_OK) != -1)							 //if it executes we return it
		return(ft_strdup(arg));
	dest = NULL;
	paths = get_pathlocation(g_ms->sh_env);				 //we copy or possible paths
	i = create_probable_str(&dest, arg, paths,i);
	while ((access(dest, X_OK)) == -1)	 				 //we check each possible path if we manage to execute we return that path
	{
		if (i >= strlen(paths) - 5)
		{
			free(dest);
			printf("error in pathfinder");//error_message();
			return(NULL);
		}
		free(dest);
		i = create_probable_str(&dest, arg, paths,i);		//creates a possible path str
	}
	return(dest);
}

char *get_pathlocation(char **envp)
{
	int i;
	i = 0;
	while((ft_strncmp("PATH=", envp[i], 5))) // we got the start location of the portion we want
		i++;
	return(envp[i]);
}

int create_probable_str(char **dest, char *arg, char *src, int i)
{
	*dest = malloc(sizeof(char) * ft_strlen((src + i)) + ft_strlen(arg) + 2);
	i = ft_strcharcpy(*dest, (src + i), ':', 0) + i;
	ft_strcat(*dest, "/");
	ft_strcat(*dest, arg);
	return(i);
}

unsigned int	ft_strcat(char *dest, char *src)
{
	unsigned int		i;
	unsigned int		b;

	i = ft_strlen(dest);
	b = ft_strlen(src) + i;
	if (!(dest))
		return (b);
	while ((*src))
		dest[i++] = *src++;
	dest[i] = 0;
	return (b);
}

unsigned int	ft_strcharcpy(char *dest, char *src, char until, unsigned int pos)
{
	unsigned int i;
	i = 0;
	if ((!dest) || (!src))
		return (0);
	while ((src[pos] != '\0' && src[pos] != until))
		dest[i++] = src[pos++];
	dest[i] = 0;
	return (++pos) ;
}
