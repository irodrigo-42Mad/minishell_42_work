/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeparse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:19:27 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/18 14:20:51 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strchlen(char *str, char car)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == car)
			return (i);
	}
	return (i);
}

void	ft_setnewpos(t_ms *s, size_t len)
{
	if (s->str[len + 1] == '|')
	{
		*s->str = *s->str + (len + 1);
		*s->pars_cmd = *s->pars_cmd + (len + 1);
	}
	else
	{
		*s->str = *s->str + len;
		*s->pars_cmd = *s->pars_cmd + len;
	}
}

t_lst	*ft_newinst(char *cmd, int *i)
{
	t_lst		*elm;
	int			len;
	static int	begin;

	elm = ft_calloc (1, sizeof(t_lst));
	elm->el_nbr = (*i) + 1;
	elm->file_in = FD_IN;
	elm->file_out = FD_OUT;
	elm->exe_state = SUCCESS;
	elm->herename = NULL;
	elm->str_cmd = ft_strdup(cmd);
	len = ft_strlen(elm->str_cmd);
	if (*i == 0)
		begin = 0;
	elm->str_line = ft_substr(g_ms->str, begin, len);
	begin += len + 1;
	ft_bzero (cmd, sizeof(cmd));
	free(cmd);
	elm->next = NULL;
	return (elm);
}
/*
// t_lst	*ft_newinst(t_ms *s, int *i)
// {
// 	t_lst	*elm;
// 	char	*tmp;
// 	char	*data; // de momento pendiente
// 	int 	j;

// 	j = *i;
// 	tmp = NULL;
// 	data = NULL;
// 	tmp = ft_strdup(s->str);
// 	elm = ft_calloc(1, sizeof(t_lst));
// 	elm->file_in = FD_IN;
// 	elm->file_out = FD_OUT;
// 	elm->exe_state = SUCCESS;
// 	elm->str_cmd = NULL;
// 	//while (tmp != NULL || data == NULL)
// 	//	data = ft_strtok(tmp, "|");
// 	//data "ls -a | wc -l"
// 	elm->aux_ln = ft_strchlen(tmp, '|');
// 	elm->str_line = ft_substr(s->pars_cmd, j, elm->aux_ln);
// 	elm->str_aux = ft_substr(tmp, j, elm->aux_ln);
// 	if (tmp[elm->aux_ln] != '\0')
// 		*i += (elm->aux_ln + 1);
// 	else
// 		*i += elm->aux_ln;
// 	// // cambiar esta funcion para quedarnos con lo que nos interesa
// 	// // o utilizar aqui la funcion strtok para dividir todos los elementos de lista.
// 	// ft_setnewpos(s, elm->aux_ln);
// 	elm->next = NULL;
// 	return (elm);
// }
*/

/*
	process->hdoc_name = NULL;
	process->next = NULL;
	process->n_hdoc = 0;
	process->line = ft_substr(*str, 0, len);
	process->line_aux = ft_substr(*aux, 0, len);
	process->line_save = process->line;
	process->line_aux_save = process->line_aux;
	pointer_mover(aux, str, len);
	return (process);
*/

/*
// t_nod	*create_pnode(char **aux, char **str, int *n_proc)
// {
// 	t_nod	*process;
// 	size_t	len;

// 	process = malloc(sizeof(t_nod));
// 	process->p_nbr = ++(*n_proc);
// 	process->fdi = 0;
// 	process->fdo = 1;
// 	process->hdoc_name = NULL;
// 	process->next = NULL;
// 	process->cmd = NULL;
// 	process->n_hdoc = 0;
// 	process->launch = OK;
// 	len = process_str_length(*aux);
// 	process->line = ft_substr(*str, 0, len);
// 	process->line_aux = ft_substr(*aux, 0, len);
// 	process->line_save = process->line;
// 	process->line_aux_save = process->line_aux;
// 	pointer_mover(aux, str, len);
// 	return (process);
// }
*/

/*
// 1.- contar todos aquellos pipes que hay en el comando para separar menos aquellos entre "" o ''
// 2.- guardarlos en una variable local que se utiliza como elemento strtok
// 3.- con ello crear la lista de comandos
*/

void	ft_prepare_command(void)
{
	t_lst	*aux;
	char	**str;
	int		i;

	if (ft_count_orders() != 1)
	{
		i = 0;
		str = ft_split(g_ms->pars_cmd, '|');
		while (str[i] != NULL)
		{
			aux = ft_newinst(str[i], &i);
			ft_setlst_type(aux);
			aux->str_cmd = expand_vars(aux->str_cmd);
			ft_set_paramlst(aux);// por aqui andamos
			ft_lstcmdadd_back(&g_ms->instr, aux);
			g_ms->prcs_n++;
			i++;
		}
		free(str);
	}
	else
		return (ft_msg(Q_ERR_05, 2));
}

void ft_setlst_type(t_lst *aux)
{
	size_t	pos;
	size_t	len;

	pos = 0;
	len = ft_strlen (aux->str_cmd);
	while (pos < len && aux->type == 0)
	{
		if (aux->str_cmd[pos] == '\"')
			aux->type = 1;
		if (aux->str_cmd[pos] == '\'')
			aux->type = 2;
		if (aux->str_cmd[pos] == '>')
		{
			aux->type = 3;
			if (aux->str_cmd[pos + 1] == '>')
				aux->type = 4;
		}
		if (aux->str_cmd[pos] == '<')
		{
			aux->type = 5;
			if (aux->str_cmd[pos + 1] == '<')
				aux->type = 6;
		}
		pos++;
	}
}

void ft_set_paramlst(t_lst *aux)
{
 size_t pos;
 size_t len;

 pos = 0;
 len = ft_strlen (aux->str_cmd);
 while (pos < len && aux->type == 0)
 {
  if (aux->str_cmd[pos] == '>' || aux->str_cmd[pos] == '<')
  {
   if (aux->str_cmd[pos + 1] == '<')
    aux->type = 3;
   if (aux->str_cmd[pos + 1] == '>')
    aux->type = 4;
  }
  else
  {
   aux->type = 1;
  }
  if (aux->str_cmd[pos] == '\"' || aux->str_cmd[pos] == '\'')
   aux->type = 2;
  pos++;
 }

 //if (aux->type != 1 && aux->type != 2)
 // aux->str_args = ft_split(aux->str_cmd, ' ');
 //if (aux->type == 2)
 // ft_quote_cmd(aux->str_cmd);


 // pa quitar despues
  aux->str_args = ft_split(aux->str_cmd, ' ');

 //1 indicar si tenemos redirecciones
 //2 si no hay redirecciones separar args
 //3 guardar nodo
}
