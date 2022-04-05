/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_local_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:47:05 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/11 12:15:51 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh_var	*ft_set_env_val(char *v_name, int val)
{
	t_sh_var	*nod;

	nod = malloc(sizeof(t_sh_var));
	nod->v_name = ft_strdup(v_name);
	nod->v_val = ft_itoa(val);
	nod->next = NULL;
	return (nod);
}

t_sh_var	*ft_set_envch_val(char *v_name, char *val)
{
	t_sh_var	*nod;

	nod = malloc(sizeof(t_sh_var));
	nod->v_name = ft_strdup(v_name);
	nod->v_val = ft_strdup(val);
	nod->next = NULL;
	return (nod);
}

void	ft_replace_local_enval(t_sh_var *nod, char *v_name, char *val)
{
	free(v_name);
	free(nod->v_val);
	nod->v_val = val;
}
// falla al añadir un nodo la segunda ocasión
void	ft_add_local_env(char *car, char *err)
{
	t_sh_var	*nod;
	t_sh_var	**aux;

	nod = g_ms->sh_envar;
	while (nod)
	{
		if (!ft_strncmp(nod->v_name, car, ft_getmax_ln(nod->v_name, car)))
		{
			ft_replace_local_enval(nod, car, err);
			break ;
		}
		if (nod->next == NULL)
			aux = &nod->next;
		nod = nod->next;
	}
	if (!nod)
	{
		nod = ft_set_envch_val(car, err);
		//FALLA EN ESTE PUNTO
		if (aux)
			(*aux) = nod;
		else
			g_ms->sh_envar = nod;
	}
}

void	ft_get_errstatus(int state)
{
	if (g_ms->flg_err == SUCCESS)
	{
		if (WIFSIGNALED(state))
			ft_updt_err(WTERMSIG(state) + 128);
		else if (WIFSTOPPED(state))
			ft_updt_err(WSTOPSIG(state));
		else if (WIFEXITED(state))
			ft_updt_err(WEXITSTATUS(state));
	}
	g_ms->flg_err = SUCCESS;
}
