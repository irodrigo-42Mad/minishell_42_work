/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_ctrl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:52:05 by irodrigo          #+#    #+#             */
/*   Updated: 2022/06/07 11:29:27 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_prompt(void)
{
	ft_create_prompt();
}

void	ft_create_prompt(void)
{
	char	*aux;
	char	*tmp;
	size_t	len;

	len = 0;
	aux = getcwd(NULL, 0);
	if (aux == NULL)
	{
		chdir("..");
		aux = getcwd(NULL, 0);
	}
	len += (ft_strlen(aux) + ft_strlen(ANSI_CYAN) + 5);
	len += ft_strlen(ANSI_RESET);
	tmp = ft_calloc(len, sizeof(char));
	tmp = ft_strcat(tmp, ANSI_CYAN);
	tmp = ft_strcat(tmp, aux);
	tmp = ft_strcat(tmp, " > ");
	tmp = ft_strcat(tmp, ANSI_RESET);
	free(aux);
	aux = NULL;
	free(g_ms->prompt);
	g_ms->prompt = tmp;
	g_ms->state = READING;
}
