/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:46:16 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/14 13:39:24 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(void)
{
	int		i;
	char	*name;

	i = 0;
	ft_updt_err(0);
	while (g_ms->sh_env[i])
	{
		name = ft_getname(g_ms->sh_env[i]);
		if (*(g_ms->sh_env[i] + ft_strlen(name) + 1) != '\\')
			printf("%s\n", g_ms->sh_env[i]);
		free(name);
		i++;
	}
}
