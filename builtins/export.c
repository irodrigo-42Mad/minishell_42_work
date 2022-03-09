
#include "../minishell.h"

int	check_export_arg(char *arg)
{
	if (ft_val_envname(*arg, STATE_Q_FAIL))
	{
		while (ft_isvalid_env_core(*arg))
			arg++;
		if (*arg == '=' || !*arg)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	parse_argument(char *arg)
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

void	check_for_local_value(char *name, char **prev_value)
{
	char	*local_value;

	local_value = get_var_value(name, EXPR_CALL);
	if (*local_value != '\\')
	{
		free(*prev_value);
		*prev_value = local_value;
	}
	else
		free(local_value);
}

void	ft_export(char **argv)
{
	int		i;
	int		arg_type;
	char	*value;
	char	*name;

	i = 1;
	ft_updt_err(0);
	if (!argv[1])
		print_ordered_env();
	while (argv[i])
	{
		arg_type = parse_argument(argv[i]);
		name = def_name(argv[i++]);
		if (arg_type != NOTDEF && arg_type != EXP_ERR)
			value = ft_strdup(argv[i - 1] + ft_strlen(name) + 1);
		if (arg_type == DEFINED)
			add_to_global_env(name, value, DEFINED);
		else if (arg_type == REDEFINED)
			overwrite_env_value(name, value);
		else if (arg_type == NOTDEF)
			add_to_global_env(name, ft_strdup("\\"), NOTDEF);
		else
			export_error(argv[i - 1], name);
	}
}

static void	order_env(void)
{
	int			i;
	int			j;
	int			k;
	char		*aux;

	k = ft_matrixlen(g_ms->sh_env) - 1;
	i = 0;
	while (i <= k)
	{
		j = i + 1;
		while (j <= k)
		{
			if (ft_strcmp(g_ms->sh_env[i], g_ms->sh_env[j]) > 0)
			{
				aux = g_ms->sh_env[j];
				g_ms->sh_env[j] = g_ms->sh_env[i];
				g_ms->sh_env[i] = aux;
			}
			j++;
		}
		i++;
	}
}

/* ((When called from export with no arguments, ))*/
/* All env entries have to be set from name=value to name="value".
 * This is carrying out that. With the exception that if export has
 * exported some variable that has not been defined, it only pops out
 * when you call export without arguments, with no value or equal 
 * sign. [export a] makes env not show a, but export withour arguments
 * will show at the end "declare -x a". I mark these special entries
 * with a \* at the start, so they can be identified and printed or
 * not when necessary.*/
void	create_propper_env_entry(char *name, char *value, int i)
{
	char	*aux1;
	char	*aux2;

	free(g_ms->sh_env[i]);
	if (*value != '\\')
	{
		aux1 = ft_strjoin(name, "=\"");
		aux2 = ft_strjoin(aux1, value);
		g_ms->sh_env[i] = ft_strjoin(aux2, "\"");
		free(aux1);
		free(aux2);
	}
	else
		g_ms->sh_env[i] = ft_strjoin("*", name);
		free(name);
		free(value);
}

void	add_commas_to_env(void)
{
	char	*aux_name;
	char	*aux_value;
	char	*aux;
	int		i;

	i = 0;
	while (g_ms->sh_env[i])
	{
		aux = g_ms->sh_env[i];
		aux_name = def_name(aux);
		while (*aux != '=')
			aux++;
		aux_value = ft_strdup(++aux);
		create_propper_env_entry(aux_name, aux_value, i);
		i++;
	}
}

void	print_ordered_env(void)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		order_env();
		add_commas_to_env();
		while (g_ms->sh_env)
		{
			if (*g_ms->sh_env[i] != '*')
				join_print("declare -x", g_ms->sh_env[i]);
			else
				join_print("declare -x", (++(g_ms->sh_env[i])));
			i++;
		}
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void join_print(char *str1, char *str2)
{
	char *tmp;

	tmp = ft_strjoin(str1,str2);
	ft_putstr_fd(tmp,1);
	ft_putchar_fd('\n',1);
	free(tmp);
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

//*****
void	create_new_environment(char *name, char *value)
{
	char	**new_env;
	char	*aux;
	int		i;

	new_env = malloc(sizeof(char *) * ((int)ft_matrixlen(g_ms->sh_env) + 2));
	i = 0;
	while (g_ms->sh_env[i])
	{
		new_env[i] = ft_strdup(g_ms->sh_env[i]);
		i++;
	}
	aux = ft_strjoin(name, "=");
	new_env[i++] = ft_strjoin(aux, value);
	new_env[i] = NULL;
	free_three_ptrs(aux, name, value);
	free_matrix(g_ms->sh_env);
	g_ms->sh_env = new_env;
}

/* There are two possibilities. If the value comes from the local
 * environment, then the environment matrix has to add a new entry
 * to it. If the value comes from the global env, then the
 * correspondent entry is the one that has to change, thus the size
 * of the matrix remains unchanged. */
void	reconstruct_environment(char *name, char *value)
{
	int		entry;
	char	*aux;

	aux = NULL;
	entry = find_env(name);
	if (entry == -1)
		create_new_environment(name, value);
	else
	{
		aux = ft_strjoin(name, "=");
		free(g_ms->sh_env[entry]);
		g_ms->sh_env[entry] = ft_strjoin(aux, value);
		free_three_ptrs(aux, name, value);
	}
}

void	check_for_already_defined(char *name, char *value)
{
	int		prev_def;
	char	*aux;

	aux = value;
	check_for_local_value(name, &value);
	if (aux == value)
		prev_def = FAIL;
	else
		prev_def = SUCCESS;
	if (prev_def == SUCCESS)
		reconstruct_environment(name, value);
	else
		create_new_environment(name, value);
}

void	add_to_global_env(char *name, char *value, int stat)
{
	if (stat == NOTDEF)
		check_for_already_defined(name, value);
	else
		create_new_environment(name, value);
}