#include "minishell.h"

/*
**	Function that allows to manage the name of a variable even
**	when it begins only with a number instead of a letter, with
**	it we return the correct name and avoid the NULL as a value
*/
char	*ft_getname(char *str)
{
	char	*name;
	int		len;

	len = 0;
	if (ft_val_envname(str[len++], STATE_Q_FAIL))
	{
		while (ft_valid_envcore(str[len]))
			len++;
	}
	else if (*str == '?')
		return (ft_strdup("?"));
	name = ft_substr(str, 0, len);
	return (name);
}

char	*ft_getvalue(char *name, int status)
{
	char	*val;

	val = ft_envchk(name);
	if (!val)
		val = ft_localchk_env(name, status);
	return (val);
}

char	*ft_envchk(char *name)
{
	int		i;
	char	*aux;
	char	*value;

	aux = ft_strjoin(name, "=");
	i = -1;
	while (g_ms->sh_env[++i])
	{
		if (!ft_strncmp(g_ms->sh_env[i], aux, ft_strlen(aux)))
			break ;
	}
	if (g_ms->sh_env[i])
		value = ft_strdup(g_ms->sh_env[i] + ft_strlen(name) + 1);
	else
		value = NULL;
	free(aux);
	return (value);
}

char	*ft_localchk_env(char *name, int status)
{
	t_sh_var	*v;

	v = g_ms->sh_envar;
	while (v)
	{
		if (!ft_strncmp(v->v_name, name, ft_getmax_ln(v->v_name, name)))
		{
			if (*v->v_val != '\\')
				return (ft_strdup(v->v_val));
		}
		v = v->next;
	}
	if (status == EXPR_CALL)
		return (ft_strdup("\\"));
	else
		return (ft_strdup(""));
}