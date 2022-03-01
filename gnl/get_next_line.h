/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eimaz-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:29:00 by eimaz-va          #+#    #+#             */
/*   Updated: 2021/01/29 13:41:58 by eimaz-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>

char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *str);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strchr(const char *s1, int c);
int				get_next_line(int fd, char **line);

#endif
