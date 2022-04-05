/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:25:01 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/04/26 18:01:50 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_error_fd(int rd)
{
	if (rd < 0)
		return (-1);
	return (rd);
}

static int	ft_convert_line(int rd, char **str, char **line)
{
	char	*tmp1;
	char	*tmp2;

	ft_error_fd(rd);
	if (!rd && !*str)
	{
		*line = ft_strdup("");
		return (0);
	}
	tmp1 = ft_strchr(*str, '\n');
	if (tmp1)
	{
		*tmp1 = '\0';
		*line = ft_strdup(*str);
		tmp2 = ft_strdup(++tmp1);
		free(*str);
		*str = tmp2;
	}
	else
	{
		*line = *str;
		*str = NULL;
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*str;
	char		*tmp;
	int			rd;

	rd = 1;
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	while (rd > 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		buff[rd] = '\0';
		if (str == NULL)
			str = ft_strdup(buff);
		else
		{
			tmp = (ft_strjoin(str, buff));
			free(str);
			str = tmp;
		}
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (ft_convert_line(rd, &str, line));
}
