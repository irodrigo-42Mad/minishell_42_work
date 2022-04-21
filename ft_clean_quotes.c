#include "minishell.h"

void ft_quote_cmd(char *str)
{
	int		quote_cnt;
	int		type;
	size_t	i;
	//size_t	begin;

	i = 0;
	type = 0;
	quote_cnt = 0;
	while(str[i])
    {
		if (str[i] == '\'' && quote_cnt % 2 == 0 && type == 0)
			type = 1;
		if (str[i] == '\"' && quote_cnt % 2 == 0 && type == 0)
			type = 2;

		// if (type == 1)
        // {
        //     if (str[i] == '\'')
		// 		quote_cnt++;
        //     if(quote_cnt % 2 != 0)
		// 	{
		// 		if (str[i + 1 ] != '\0')
		// 			str[i] = str[i + 1];
		// 		else
		// 		{
		// 			type = 0;


		// 	}

        //         begin = (i + 1);
        //     else
		// 	{
        //         // obtener la subcadena
        //         // aqui ya tenemos que tener contadas las ""
        //         elm = calloc(((i - begin) + 1),sizeof(char));
        //         strncpy(elm, &data[begin], (i - begin));
        //         elm[((i - begin) + 1)]  = '\0';
        //         dquote_cnt = 0;
        //     }
        // }
        i++;


	// pos = 0;
	// len = ft_strlen(str);
	// aux = ft_strdup(str);
	// while (str[pos] != '\"' && str[pos] != '\'' && str[pos] != '\0')
	// {
	// 	if (str[pos] == '\'')
	// 		state = 1;
	// 	if (str[pos] == '\"')
	// 		state = 2;



	// 	pos++;
	// }
	// printf ("%s, %lu\n", str, pos);



	}


}
