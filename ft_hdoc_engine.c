#include "minishell.h"

void	ft_set_hdoc(t_lst *lst)
{
	char	*eof;
	char	*tmp;

// en este momento, cuando llegamos aqui, tenemos el elemento
// y sabemos si es un nodo heredoc o no
// si lo es, tenemos que poner lo necesario a true
// sino, hacer la redireccion.
	lst->str_aux = ft_strdup(lst->str_cmd);
	lst->str_save = ft_strdup(lst->str_line);
	tmp = lst->str_aux;
	while (*tmp != '\0')
	{
		tmp = ft_strnstr(tmp, "<<", ft_strlen(tmp));
		if (tmp == NULL)
			break ;
		else
		{
			tmp += 2;
			ft_set_strpntr(&tmp, &lst->str_aux, &lst->str_line, 2);
			lst->herename = ft_strdup(lst->str_line);
			return ;
		}
		eof = ft_eofcatch(&lst->here_num, &lst->str_line);
		// hasta aqui todo ok

		// en este punto debemos de abrir el heredoc
		//open_heredoc(eof, lst);
	}
	if (lst->file_in != 0)
		close(lst->file_in);
	lst->file_in = 0;
	//ft_hdc_prepareln(lst); // falta esto, ando por aqui
}

char	*ft_eofcatch(int *hd_num, char **dat_line)
{
	char	*str;
	char	*tmp;
	char	*eof;
	int		ln;

	ln = (ft_str_bash_len(*dat_line, FAIL) + 1);
	tmp = malloc(sizeof(char) * ln);
	eof = tmp;
	str = *dat_line;
	ln--;
	while (ln > 0)
	{
		if (*str != '*')
		{
			*tmp++ = *str;
			ln--;
		}
		*str++ = ' ';
	}
	*tmp = '\0';
	*(--str) = '\\';
	*hd_num += 1;
	return (eof);
}

void	ft_hdc_prepareln(t_lst *lst)
{
	int		pos;
	char	*tmp;

	pos = (lst->here_num + 1);
	printf("cmd: %s\n", lst->str_cmd);
	printf("aux: %s\n",lst->str_aux);
	printf("line: %s\n", lst->str_line);
	printf("aux save:%s\n", lst->str_aux_save);
	printf("save: %s\n",lst->str_save);
	// ojo con este cacho código, tengo que revisar
	// esta linea siguiente está causando un segfault
	tmp = lst->str_aux_save;  // esto falla al inicializar
	while ((--pos > 1) && *tmp != '\0')
	{
		tmp = ft_strnstr(tmp, "\\", ft_strlen(tmp));
		*tmp = ' ';
	}
	tmp = ft_strnstr(tmp, "\\", ft_strlen(tmp));
	if (tmp != NULL)
		return ;
	tmp++;
	while (*tmp == '*' && *tmp != '\0')
		*tmp++ = ' ';
	lst->str_line = lst->str_aux_save;
}
