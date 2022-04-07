/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:47:20 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/14 14:55:25 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char **argv)
{
	int	i;
	int	error;

	i = 1;
	ft_updt_err(0);
	while (argv[i])
	{
		error = check_unset_arg(argv[i]);
		if (!error)
			remove_from_env(argv[i]);
		else
			ft_updt_err(1);
		i++;
	}
}

int	check_unset_arg(char *arg)
{
	if (ft_val_envname(*arg, STATE_Q_FAIL))
	{
		while (ft_valid_envcore(*arg))
			arg++;
		if (!*arg)
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

void	remove_from_env(char *name)
{
	int		i;
	char	*aux;

	i = 0;
	aux = ft_strjoin(name, "=");
	while (g_ms->sh_env[i])
	{
		if (!ft_strncmp(aux, g_ms->sh_env[i], ft_strlen(aux)))
		{
			unset_entry(i);
			break ;
		}
		i++;
	}
	free(aux);
	delete_node(name);
}

void	unset_entry(int to_remove)
{
	int		len;
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_matrixlen(g_ms->sh_env);
	new_env = malloc(sizeof(char *) * len);
	while (g_ms->sh_env[i])
	{
		if (i != to_remove)
			new_env[j++] = ft_strdup(g_ms->sh_env[i]);
		i++;
	}
	new_env[j] = NULL;
	free_matrix(g_ms->sh_env);
	g_ms->sh_env = new_env;
}

void	delete_node(char *name)
{
	t_sh_var	*node;
	t_sh_var	*prev_node;

	node = g_ms->sh_envar;
	prev_node = NULL;
	while (node)
	{
		if (!ft_strncmp(node->v_name, name, ft_maxlen(node->v_name, name)))
		{
			prev_node->next = node->next;
			free(node->v_name);
			free(node->v_val);
			free(node);
			break ;
		}
		prev_node = node;
		node = node->next;
	}
}
