/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshellmsg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:24:10 by irodrigo          #+#    #+#             */
/*   Updated: 2022/03/06 14:25:13 by irodrigo         ###   ########.fr       */
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

# define T_ERR_01	"syntax error near unexpected token `"
# define T_ERR_02	"found forbiden char `"
# define T_ERR_03	": numeric argument required\n"
# define T_ERR_04	"too many arguments\n"

// other msg shell constants

#endif