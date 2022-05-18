/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:22:45 by irodrigo          #+#    #+#             */
/*   Updated: 2022/05/18 09:39:23 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_check_redir(t_lst *lst)
{
 char *st_aux;
 size_t pos;

 pos = 0;
 while (lst->exe_state == SUCCESS && lst->str_aux[pos] != '\0')
 {
  if (lst->str_aux[pos] == '>' || lst->str_aux[pos] == '<')
  {
   if (lst->str_aux[pos + 1] == '>')
   {
    pos+= 2;
    //realizar una cadena que tome la posicion del caracter
    // necesario para tomar el nombre de la redireccion
    //

    st_aux = ft_calloc((ft_strlen(lst->str_aux) - pos) + 1,
       sizeof(char));
    // aqui se obtiene el nombre del fichero de salida
    // si está entre "" obtendremos nombre igual


    if (lst->str_aux[pos] != '\"')
     ft_strnlcpy(st_aux, lst->str_aux, pos,
      (ft_strlen(lst->str_aux) - pos));
    else
     ft_strnlcpy(st_aux, lst->str_line, pos,
      (ft_strlen(lst->str_aux) - pos));

//pos = ft_take_fname(lst, pos,)
    ft_control_out_mode(st_aux,lst,APPEND);

    //st_aux += 2;
    //ft_redir(,lst,FD_OUT, MULTIPLE);
    //ft_redir(&st_aux, lst, FD_OUT, MULTIPLE);
   }
   else
   {
     if (lst->str_aux[pos + 1] == '>')
    {
     pos++;
     st_aux = ft_calloc((ft_strlen(lst->str_aux) - pos) + 1,
       sizeof(char));

     // tomar el nombre del fichero

//pos = ft_take_fname(lst, pos,)
      ft_control_out_mode(st_aux, lst, TRUNCATE);
     //ft_redir(&st_aux, lst, FD_OUT, UNIQUE);
    }
    else
    {
     //pos = ft_take_fname(lst, pos,)



     size_t mlen;
     mlen = (ft_strlen(lst->str_aux) - pos) + 1;
     st_aux = ft_calloc((ft_strlen(lst->str_aux) - pos) + 1,
       sizeof(char));
     pos+= 2;

     //ft_strnlcpy(st_aux, lst->str_aux, pos,
     // (ft_strlen(lst->str_aux) - pos));
    if (lst->str_aux[pos] != '\"')
     ft_strnlcpy(st_aux, lst->str_aux, pos,
      (ft_strlen(lst->str_aux) - pos));
    else
     ft_strnlcpy(st_aux, lst->str_line, pos,
      (ft_strlen(lst->str_aux) - pos));

     ft_indirection(st_aux, lst);
     //ft_redir(&st_aux, lst, FD_OUT, UNIQUE);

    }
   //  if (*st_aux++ == '>')
   //   ft_redir(&st_aux, lst, FD_OUT, UNIQUE);
   //  else
   //   ft_redir(&st_aux, lst, FD_IN, UNIQUE);
   }
  }
  else
   pos++;
 }
}
// revisar que tenemos que hacer con las redirecciones.


char *ft_obtain_file(t_lst *lst, char **str_line)
{
 char *aux;
 char *file;
 int  len;

 //len = string_length_bash(*str_line, SUCCESS);
 len = ft_set_lenv(*str_line, PARAM);
 //add_envar_len(&len, *str_line, PARAM);
 file = malloc(sizeof(char) * (len + 1));
 aux = file;
 ft_set_strandenv(&aux, str_line, lst, &len);
 //write_str_w_envar(str_line, &aux, &len, lst);
 return (file);
}

void ft_redirections(void)
{
 int  i;
 t_lst *elm;

 i = 0;
 elm = g_ms->instr;
 while (i++ < g_ms->prcs_n)
 {
  if (elm->exe_state == SUCCESS)
  {
   ft_check_redir(elm);    // revisando este de aquí
   ft_clean_hdoc_pos(elm); // este funciona ok
  }
  elm = elm->next;
 }
}
