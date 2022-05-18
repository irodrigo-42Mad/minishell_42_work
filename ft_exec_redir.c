/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:46:12 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/18 13:32:23 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h> 

int  ft_dircheck(char *file)
{
 DIR  *rst_dir;

 rst_dir = opendir(file);
 if (rst_dir)
 {
  closedir(rst_dir);
  return (ft_element_error(file, -126));
 }
 return (0);
}




// void ft_redir(char **str, t_lst *lst, int dir, int mode)
// {
//  int  new_pos;
//  char *file;







//  //ft_set_strbegin();

//  //place_str_pointers(aux, &lst->line_aux, &lst->line, red);
//  file = *str;

//  //lst->str_line = ft_strdup(lst->str_cmd);
//  file = ft_obtain_file(lst, &lst->str_line);
//  if (lst->exe_state == SUCCESS)
//  {
//   if (mode == FD_OUT && dir == MULTIPLE)
//    ft_control_mode(file, lst, APPEND);
//   else if (mode == FD_OUT && dir == UNIQUE)
//    ft_control_mode(file, lst, TRUNCATE);
//   else
//    ft_new_input(file, lst);
//  }
//  free(file);
//  new_pos = lst->str_line - lst->str_save;
//  new_pos -= (lst->str_aux - lst->str_aux_save);

//  // ahi que mirar como movemos la position
//  ft_locate_strptr(new_pos, &lst->str_aux, str);
//  //move_str_pointers(new_pos, &lst->str_aux, str);
// }

void ft_control_out_mode(char *file, t_lst *lst, int mode)
{
 if (lst->file_out != 1)
   close(lst->file_out);
 if (ft_dircheck(file) < 0)
  return ;
 if (mode == APPEND)
 {
  if(access(file, W_OK) != 0)
   lst->file_out = open(file, O_RDWR| O_APPEND);
  else
   lst->file_out = open(file, O_RDWR| O_CREAT, S_IRWXU);
 }
 else if (mode == TRUNCATE)
 {
  if (access(file, R_OK) != 0)
   unlink(file);
  lst->file_out = open(file, O_RDWR| O_CREAT, S_IRWXU);
 }
 if (lst->file_out == -1)
  ft_write_file_err(lst, file);
}

void ft_indirection(char *file, t_lst *lst)
{
 //fd = check_for_hdoc_priority(lst->str_line);
 if (!ft_dircheck(file))
 {
  //if (lst->herename)
   // si es el último heredoc, debemos llenar el archivo con el contenido de este
   // de forma correcta.
  // unlink_one_heredoc(&(node->hdoc_name));


  // el hdoc estará ya creado, lo que es necesario es ajustarlo correctamente
  // en el los ficheros en los que tiene que aparecer
  if (access(file, R_OK) != 0)
   ft_write_file_err(lst, file);
  lst->file_in = open(file, O_RDONLY);
  if (lst->file_in == -1)
   ft_write_file_err(lst, file);
 }
}
