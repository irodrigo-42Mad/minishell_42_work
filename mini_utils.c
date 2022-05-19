/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatman <hatman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:32:24 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/19 18:25:44 by hatman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exit(t_ms *s)
{
	ft_bzero(s->prompt, ft_strlen(s->prompt));
	clear_history();
	(void)s;
	exit(0);
}

void	cmd_pwd(t_ms *s)
{
	char	buffer[2000];

	(void)s;
	printf("%s\n", getcwd(buffer, sizeof(buffer)));
}

void	cmd_clear(void)
{
	const char	*clear_screen_ansi = "\e[1;1H\e[2J";

	write(STDOUT_FILENO, clear_screen_ansi, 11);
}

void	cmd_notfound(t_ms *s)
{
	printf("%s: command not found\n", s->pars_cmd);
}

void	ft_put_banner(void)
{
	printf("%s%s%s%s\n", CYAN, MSG001_1, MSG001_2, RESET);
	printf("%s%s%s%s\n", CYAN, MSG002_1, MSG002_2, RESET);
	printf("%s%s%s%s\n", CYAN, MSG003_1, MSG003_2, RESET);
	printf("%s%s%s%s\n", CYAN, MSG004_1, MSG004_2, RESET);
	printf("%s%s%s%s\n", CYAN, MSG005_1, MSG005_2, RESET);
	printf("%s%s%s%s\n", CYAN, MSG006_1, MSG006_2, RESET);
	printf("%s%s%s%s\n", CYAN, MSG007_1, MSG007_2, RESET);
	printf("%s%s%s%s\n", CYAN, MSG008_1, MSG008_2, RESET);
	printf("%s%s%s\n", CYAN, MSG009, RESET);
}
