#include <stdio.h>
#include "libft/libft.h"

const size_t	ft_set_quote_pos(int flg, char *str, size_t pos)
{
	size_t	last;
	char	quote;

	last = 0;
	if (flg == 1)
		quote = '\'';
	if (flg == 2)
		quote = '\"';
	while (str[pos] != quote && flg > 0)
	{
		if (str[pos] != quote)
		{
			pos++;
			last++;
		}
		else
			flg = 0;
	}
	return (last);
}

const size_t	ft_set_end(char *str, int pos)
{
	size_t	last;

	last = 0;
	while (str[pos] != ' ')
	{
		pos++;
		last++;
	}
	return (last);
}

int	main(void)
{
	char	*aux;
	char	*file;
	size_t	pos;
	size_t	len;
	size_t	end;
	size_t	begin;

	aux = "cat >> \'amigo \"como\" estamos\' <> cosa > \"vamos a hacer redirecciones\"";
	len = ft_strlen(aux);
	pos = 0;
	while (pos < len)
	{
		if (aux[pos] == '>' || aux[pos] == '<')
		{
			if (aux[pos + 1] == '>')
			{
				pos += 3;
				if (aux[pos] == '\"' || aux[pos] == '\'')
				{
					begin = ++pos;
					if (aux[pos - 1] == '\'')
						end = ft_set_quote_pos(1, aux, pos);
					else
						end = ft_set_quote_pos(2, aux, pos);
				}
				else
				{
					begin = pos;
					end = ft_set_end(aux, pos);
				}
				file = (char *) malloc(sizeof(char) * (end + 1));
				ft_strnlcpy(file, aux, begin -1, (end + 1));
				// en este momento se hace la expansión de variables de entorno
				// y se imprime
				printf("%s\n", file);
				free(file);
			}
		}
		pos++;
	}
	return (0);
}
