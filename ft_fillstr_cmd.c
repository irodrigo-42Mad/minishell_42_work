/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillstr_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrau <mgrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:06:50 by mgrau             #+#    #+#             */
/*   Updated: 2022/05/18 10:27:35 by mgrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_set_flg(char c, int flg)
{
 if (flg == 0)
 {
  if (c == '\'')
   flg = 1;
  if (c == '\"')
   flg = 2;
 }
 else if (flg == 1)
 {
  if (c == '\'')
   flg = 0;
 }
 else
 {
  if (c == '\"')
   flg = 0;
 }
 return (flg);
}

char *ft_prepare_aux(char *aux)
{
 int  flg;
 int  pos;
 int  len;

 flg = 0;
 pos = -1;
 len = (int)ft_strlen(aux);
 while (++pos < (len - 1) && aux[pos])
 {
  if (aux[pos] == '\"' || aux[pos] == '\'')
  {
   flg = ft_set_flg(aux[pos], flg);
   pos++;
  }
  if (aux[pos] == ' ' && flg == 0)
   aux[pos] = '|';
 }
 return (aux);
}

// static char* ft_fillcmd_args(char *elm, char *cmd, int pos, int end)
// {
//  int i;


//  i = 0;

// }

// static void ft_set_finalstr(char **elements, char *str)
// {
//  int  i;
//  int  pos;
//  int  end;
//  char *data;
//  size_t len;
//  //size_t piece_ln;

//  i = -1;
//  pos = 0;
//  while (elements[++i])
//  {
//   len = ft_strlen(elements[i]);
//   data = (char *) malloc (sizeof(char) * (len + 1));
//   ft_strnlcpy(data, str, pos - 1 , len + 1);
//   if (precise_cmp(elements[i], data, len))
//    pos += ++len;
//   else
//   {
//    end = len;
//    ft_strnlcpy(elements[i], str, pos, end);
//    if (elements[i][ft_strlen(elements[i]) - 1] == '\"'
//     || elements[i][ft_strlen(elements[i]) - 1] == '\'')
//     elements[i][ft_strlen(elements[i]) - 1] = '\0';
//    printf("%s\n\n", elements[i]);
//    pos += ++len;
//   }


//   //printf ("pos: %d caracter: %c\n ", pos, str[pos]);
//   free (data);
//  }
// }

// int main (void)
// {
//  char *aux;
//  char *other;
//  char **elements;
//  int i=-1;
//  char *cadena;

//  aux = "echo \"                \" / \'                  \'";
//  other = "echo \"hola \'que\' $haces / \"como te encuentras\"";
//  cadena = ft_strdup(aux);
//  elements = ft_split(ft_prepare_aux(cadena), '|');
//  ft_set_finalstr(elements, other);
//  while (elements[++i])
//   printf ("Element: %s\n", elements[i]);
//  free (cadena);
//  return (0);
// }
