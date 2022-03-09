#include "minishell.h"

void	ft_set_hdoc(t_lst *lst)
{
	char	*eof;
	char	*tmp;

	tmp = lst->str_line;
	while (*tmp != '\0')
	{
		tmp = ft_strnstr(tmp, "<<", ft_strlen(tmp));
		if (tmp == NULL)
			break ;
		else
		{
			tmp += 2;
			ft_set_strpntr(&tmp, &lst->str_line, &lst->str_aux, 2);
		}
		eof = ft_eofcatch(&lst->here_num, &lst->str_aux);
		//eof = eof_gatherer(&lst->aux_ln, &lst->herename);
		//open_heredoc(eof, lst);
	}
	if (lst->file_in != 0)
		close(lst->file_in);
	lst->file_in = 0;
	ft_hdc_prepareln(lst);
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
	// ojo con este cacho código, tengo que revisar
	// esta linea siguiente está causando un segfault
	tmp = lst->str_aux_save;
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