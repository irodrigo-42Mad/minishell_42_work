/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mshell_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:50:57 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/14 08:32:12 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strtok(char *str, char *delim)
{
	static char	*pos;
	char		*new;

	if (str)
		pos = str;
	if (!pos)
		return (NULL);
	while (*pos && ft_strchr(delim, *pos))
		pos++;
	new = pos;
	while (*new && !ft_strchr(delim, *new))
		new++;
	str = pos;
	if (new > pos)
	{
		pos = new + (*new != 0);
		*new = '\0';
		return (str);
	}
	pos = NULL;
	return (NULL);
}
