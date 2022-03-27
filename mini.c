/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:43:22 by mgrau             #+#    #+#             */
/*   Updated: 2022/03/11 14:35:48 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	hola(void)
** {
** 	system("leaks minishell");
** }
**
**void	get_cmd(t_ms *s)
**{
**	int		i;
**	int		len;
**	char	*aux;
**
**	i = 0;
**	len = 0;
**
**	while (s->str[len] != '\0' && !ft_isspace(s->str[len]))
**		len++;
**	//printf("\n\nlen del cmd:%d\n\n", len);
**	s->cmd = malloc(sizeof(char) * len);
**	while (i < len)
**	{
**		//printf("cmd[%d]: %c\n", i, s->cmd[i]);
**		s->cmd[i] = s->str[i];
**		i++;
**	}
**	aux = ft_strdup(ft_substr(s->str, len + 1, ft_strlen(s->str)));
**	//printf("despues del comando: %s\n", aux);
**	free (s->str);
**	s->str = aux;
**	//printf("%s\n", s->str);
**	s->cmd[i] = '\0';
**}
*/

/*
** lineas de control y de correccion para la funcion exit
**
** // printf("cmd:%s\n", s->cmd);
** // printf("cmd:%s\n", s->str);
** //atexit(hola);
*/
void	cmd_exit(t_ms *s)
{
	ft_bzero(s->prompt, ft_strlen(s->prompt));
	clear_history();
	(void)s;
	exit(0);
}

/*char	*get_cwd(char *buffer, size_t size)
{
	(void)buffer;
	(void)size;
}*/

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

/*
** para pruebas de la funcion anterior
** //ft_put_banner();
** // funcion a revisar para limpiar la pantalla
** //system("clear");
*/

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

void ch_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	char *aux = "ls -a |wc -l |grep 1 >dev_null" ;

	//atexit(ch_leaks);
	if (argc != 1)
		exit(ft_msg_val(Q_ERR_04, 42));
	g_ms = malloc(sizeof(t_ms));
	if (!g_ms)
	 	exit(ft_msg_val(M_ERR_01, 42));
	ft_initialize(argc, env);
	ft_put_banner();
	ft_set_signal();
	while (TRUE)
	{
		ft_set_prompt();
		//g_ms->str = readline(g_ms->prompt);
		g_ms->str = ft_strdup(aux);
		// 	controlar los espacios y tabuladores ! hecho
	 	if (ft_strlen(g_ms->str) > 0  &&
		 	ft_check_spc(g_ms->str) != 1)
	 	{
			add_history(g_ms->str);
	 		if (!ft_parser()) // la segunda vez se pira
			//if (!ft_parser(g_ms))
	 		{
				// hasta aqui todo ok
				ft_prepare_command(g_ms);
	// 			//ft_heredoc();
	// 			ft_redirections(g_ms);
	// 			// other redirs
	 			start_executer();
	// 			ft_clean_instr(g_ms->instr);
			}
			ft_pre_clean(g_ms);
	// 			//clean list si no explota en este punto
	// 			//free (g_ms->str);
	  	}
	}

	// 	// hasta aqui revisado
	// 	//g_ms->pars_cmd = ft_strdup(g_ms->str);

	// 	// la linea siguiente da un segfault pero no es valida para el proyecto final
	// 	//if (!(ft_strncmp(g_ms->pars_cmd, "exit", ft_strlen(g_ms->pars_cmd))))
	// 	//	cmd_exit(g_ms);

	// 	//free (g_ms->str);
	// 	// liberar la lista



	// 	//free (g_ms->str);
	// }
	ft_pre_clean(g_ms);
	free (g_ms);





	// 	//ft_parser(&s);
	// //	ft_strlcpy (s.str,"hola\0",5);
	// //	ft_strlcpy (s.cmd,"hola\0",5);
	// 	//ft_prepare_command(&s);
	//
	// 	if (g_ms.str != NULL)
	// 		add_history (g_ms.str);
	// 	if (!ft_parser(&g_ms))
	// 	{
	// 		ft_prepare_command(&g_ms);
	// 	}
	// //	ft_quotes_threat(&s.str);
	// //	ft_redir_pipes(0, &s.str);
	// 	//s.cmd = ft_strdup(s.str);
	// system ("leaks minishell");
	// printf("Hola\n");
	// 	//TODO parsear el elemento y tokenizarlo
	// 	//get_cmd(&s);  // esta función tiene leaks

	// 	if (!(ft_strncmp(g_ms.cmd, "exit", ft_strlen(g_ms.cmd))))
	// 		cmd_exit(&g_ms);
	// 	free (g_ms.cmd);
	// 	free (g_ms.str);
	//}
	/*while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');


	write(1, "minishell-0.0$ --> ", 19);
	while (1)
	{

		get_next_line(0, &s.str);
		get_cmd(&s);
		if (!s.str || !s.cmd)
			return (0);
		if (!(ft_strncmp(s.cmd, "exit", ft_strlen(s.cmd))))
			cmd_exit(&s);
		else if (!(ft_strncmp(s.cmd, "echo", ft_strlen(s.cmd))))
			cmd_echo(&s);
		else if (!(ft_strncmp(s.cmd, "pwd", ft_strlen(s.cmd))))
			cmd_pwd(&s);
		else if (!(ft_strncmp(s.cmd, "clear", ft_strlen(s.cmd))))
			cmd_clear();
		else
			cmd_notfound(&s);
		write(1, "minishell-0.0$ --> ", 19);
		free (s.cmd);
		free (s.str);
	}*/
	return (0);
}

/*
** void	cmd_echo(t_ms *s)
** {
** 	int		len_flag;
** 	int		ini_pos;
** 	int		i;
** 	char	*rest;
** 	char	*aux;
**
**	aux = NULL;
**	i = 0;
**	ini_pos = 0;
**	len_flag = 0;
**	//printf("llega line:%s\n", s->str);
**	while (s->str[len_flag] != '\0' && !ft_isspace(s->str[len_flag]))
**		len_flag++;
**
**	//printf("len_flag:%d\n", len_flag);
**	s->flag = ft_substr(s->str, 0, len_flag);
**	rest = malloc(sizeof(char) * (ft_strlen(s->str) - len_flag));
**	while (s->str[len_flag] != '\0')
**	{
**		rest[i] = s->str[len_flag];
**		i++;
**		len_flag++;
**	}
**	//printf("flag:%s\n", s->flag);
**	//printf("rest:%s\n", rest);
**	//TODO: \n == \0 quitar espacios
**	if (!(ft_strncmp(s->flag, "-n", ft_strlen(s->flag))))
**	{
**		i = 0;
**		while (ft_isspace(rest[i]) || rest[i] == '"')
**			i++;
**
**			//printf("rest[%d]:%s\n", i, rest);
**		//printf("DOSrest:%c\n", rest[len_flag - 3]);
**
**		if (rest[len_flag -3] == '"')
**		{
**			//write (1, "hola", 5);
**			aux = ft_substr(rest, i, len_flag - 4);
**			aux[len_flag - 4] = '\0';
**			write (1, aux,ft_strlen(aux) - 1);
**		}
**		else
**		{
**			//write (1, "adios", 6);
**			aux = ft_substr(rest, i, len_flag - 3);
**			aux[len_flag - 3] = '\0';
**			write (1, aux,ft_strlen(aux));
**		}
**		//printf("aux[%d]:%s\n", len_flag, aux);
**		//printf("FALTAQUITARELENTER%s\n", aux);
**	}
**		j = 0;
**		printf("rest[%d]:%s", i, rest);
**		while (rest[i] != '\0')
**		{
**			aux[j] = rest[i];
**			j++;
**			i++;
**		}
**		aux[j] = '\0';
**		//printf("i:%d\n", i);
**		printf("%s\n", aux);
**	}
**	else
**	{
**		int end=0;
**		i = 0;
**		if (s->str[0] == '"')
**			i = 1;
**		if (s->str[ft_strlen(s->str) - 1] == '"')
**			end = ft_strlen(s->str) - 2;
**		else
**			end = ft_strlen(s->str);
**		write (1, ft_substr(s->str, i, end), end);
**		write (1, "\n", 1);
**
**		//if (s->str[ft_strlen(s->str) - 2])
**		//printf("%c", s->str[ft_strlen(s->str) - 1]);
**		//printf("%s\n", s->str);
**	}
**	// cosas que faltan del echo.....
**	// el echo toma valores con colores siempre que se le indique en el terminal
**	// el echo no muestra comillas simples
**	// el echo
**}
*/
