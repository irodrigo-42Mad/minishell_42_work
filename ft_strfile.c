#include "minishell.h"


void ft_rebuild_str(t_lst *lst)
{
	printf ("aux: %s\n", lst->str_aux);
	printf ("line: %s\n", lst->str_line);
	printf ("cmd: %s\n", lst->str_cmd);
	printf ("aux save: %s\n", lst->str_aux_save);
	printf ("save: %s\n", lst->str_save);
	ft_bzero (lst->str_aux_save, ft_strlen(lst->str_aux_save));
	free(lst->str_aux_save);

}


void	ft_restore_str_command(void)
{
	t_lst *aux;

	int i_pr;

	aux = g_ms->instr;

	while (aux)
	{
		i_pr = 0;

		while (aux->str_cmd[i_pr])
		{
			if (aux->str_cmd[i_pr] == '\'' || aux->str_cmd[i_pr] == '\"')
			{

				printf("el comando %d tiene comillas\n", aux->el_nbr);

			}
			i_pr++;
		}

		printf ("%d, %s\n", aux->el_nbr, aux->str_cmd);
		aux = aux->next;
	}
	free (aux);


	printf ("%s\n", g_ms->str);
	printf ("Hola, estoy montando la cadena\n");
	return ;

}
