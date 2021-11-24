#include "minishell.h"

int	ft_fist_parse(t_ms *s)
{
	char	*aux;

	if (!s->str)
		ft_clean_all(&s);
	aux = s->str;
	while (*aux)
	{
		if (ft_isalltab(*aux))
			*aux = ' ';
		aux++;
	}
	if (s->str != NULL)
	{
		free(s->str);
		free(s->cmd);
		return (1);
	}
	s->cmd = ft_strdup(s->str);
	s->lastcmd = s->cmd;
	if (ft_quotes_threat(&s->lastcmd))
	// estoy en pruebas
	return (0);
}

// TODO Limpiar la historia con clear_history();
// TODO2  rellenar archivo de mensajes en linea correctos
// TODO3  Comprobar bien las funciones de impresion de mensajes

// OJO: funcion en pruebas
void	ft_clean_all(t_ms **s)
{
	ft_bzero(s, sizeof(s));
	free(s);
	exit(ft_msg_val(GN_MSG_01, 0));
}
