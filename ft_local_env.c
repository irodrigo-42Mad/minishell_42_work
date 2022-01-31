#include "minishell.h"

t_var	*ft_set_env_val(char *name, char *value)
{
	t_var	*nod;

	nod = malloc(sizeof(t_var));
	nod->v_name = name;
	nod->v_val = value;
	nod->next = NULL;
	return (nod);
}
