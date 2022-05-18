/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshellmsg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:24:10 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/17 12:05:43 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELLMSG_H
# define MSHELLMSG_H

// general interest msg constants
# define GN_MSG_01  "exit\n"
# define GN_MSG_02	"Minishell: "
# define GN_MSG_03	"minishell: exit: "

// error shell msg constants
# define Q_ERR_01	"unclosed dquotes were found on command\n"
# define Q_ERR_02	"unclosed squotes were found on command\n"
# define Q_ERR_03	" command not found\n"
# define Q_ERR_04	"Scripting commands and functions are not implemented\n"
# define Q_ERR_05	"Or command not implemented or pipe number error\n"

# define M_ERR_01	"Couldn't allocate memory for shell implementation\n"

# define T_ERR_01	"syntax error near unexpected token `"
# define T_ERR_02	"found forbiden char `"
# define T_ERR_03	": numeric argument required\n"
# define T_ERR_04	"too many arguments\n"
# define T_ERR_05	"error in dup2"
# define T_ERR_06	"error in execve"
# define T_ERR_07	"error in exec redir"

// other msg shell constants

#endif
