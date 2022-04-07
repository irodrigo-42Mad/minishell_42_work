/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:46:40 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/14 13:42:56 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(char **argv)
{
	int		i;
	int		arg_type;
	char	*value;
	char	*name;

	i = 1;
	ft_updt_err(0);
	if (!argv[1])
		print_env();
	while (argv[i])
	{
		arg_type = parse_arg(argv[i]);
		name = def_name(argv[i++]);
		if (arg_type != NOTDEF && arg_type != EXP_ERR)
			value = ft_strdup(argv[i - 1] + ft_strlen(name) + 1);
		if (arg_type == DEFINED)
			ft_add_envglob(name, value, DEFINED);
		else if (arg_type == REDEFINED)
			overwrite_env_value(name, value);
		else if (arg_type == NOTDEF)
			ft_add_envglob(name, ft_strdup("\\"), NOTDEF);
		else
			export_error(name);
	}
}

void	export_error(char *name)
{
	free(name);
	ft_updt_err(1);
}

int	parse_arg(char *arg)
{
	char	*name;
	int		name_entry;

	if (check_export_arg(arg))
	{
		name = def_name(arg);
		if (!*(arg + ft_strlen(name)))
		{
			free(name);
			return (NOTDEF);
		}
		name_entry = find_env(name);
		free(name);
		if (name_entry == -1)
			return (DEFINED);
		else
			return (REDEFINED);
	}
	else
		return (EXP_ERR);
}

int	check_export_arg(char *arg)
{
	if (ft_val_envname(*arg, STATE_Q_FAIL))
	{
		while (ft_valid_envcore(*arg))
			arg++;
		if (*arg == '=' || !*arg)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	find_env(char *name)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strjoin(name, "=");
	while (g_ms->sh_env[i])
	{
		if (!ft_strncmp(g_ms->sh_env[i], aux, ft_strlen(aux)))
		{
			free(aux);
			return (i);
		}
		i++;
	}
	free(aux);
	return (-1);
}
