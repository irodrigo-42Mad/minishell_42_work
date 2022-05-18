#include "minishell.h"

void  ft_clear_str(char *str, t_lst *lst)
{
 int ln;
 int pos;
 int flg;
 /** comentario a eliminar más adelante **/
 // cuando la cadena del heredoc lleva "" no calcula
 // correctamente la última posicion, falla este procedimiento
 // al limpiar las cadenas del elemento  SOLUCIONADO

 ln = (int)(ft_strlen(lst->str_save) - ft_strlen(str));
 pos = -1;
 flg = 0;
 while (++pos <= ln)
 {
  if (flg == 0 && lst->str_save[pos] == '<')
   if (lst->str_save[pos + 1] == '<')
    flg = 1;
  if (flg == 1)
   lst->str_save[pos] = ' ';
 }
 lst->str_save[pos] = '\\';
 /** comentario a eliminar más adelante **/
 // necesario para eliminar las últimas comillas
 // en el caso de que las tenga el nombre
 if (lst->str_save[pos + 1] == '\"')
  lst->str_save[pos + 1] = ' ';
}

void ft_mute_aux(char *str, char *str2)
{
 size_t pos;
 size_t ln;
 int  flg;

 flg = 0;
 pos = 0;
 ln = ft_strlen(str);
 while (ln-- > 0 && str[pos] != '\0')
 {
  if ((str[pos] == '\"') && flg == 0)
  {
   flg = 1;
   pos++;
  }
  if ((str[pos] == '\'') && flg == 0)
  {
   flg = 2;
   pos++;
  }
  if (flg > 0)
  {
   str[pos] = str2[pos];
   if (str[pos] == '\"' && flg == 1)
    flg = 0;
   if (str[pos] == '\'' && flg == 2)
    flg = 0;
  }
  pos++;
 }
}

void ft_rebuild_str(t_lst *lst)
{
 ft_bzero(lst->str_aux, ft_strlen(lst->str_aux));
 // de momento no hace falta este fragmento de código,
 // se puede eliminar sin problema

 //ft_bzero(lst->str_line, ft_strlen(lst->str_line));
 //lst->str_line = ft_strdup(lst->str_save);
 lst->str_aux = ft_strdup(lst->str_save);
 ft_mute_aux(lst->str_aux, lst->str_cmd);
 lst->str_aux_save = ft_strdup(lst->str_aux);
}


// este procedimiento montará los comandos para ejecutar

void ft_restore_str_command(void)
{
 t_lst *aux;
 int  len;
 int  end;
 char *element;
 int  pos;
 int  i_pr;

 aux = g_ms->instr;
 while (aux)
 {
  i_pr = -1;
  // preparamos el comando
  aux->str_args = ft_split(ft_prepare_aux(aux->str_cmd), '|');
  pos = 0;
  while (aux->str_args[++i_pr])
  {
   //printf ("str_line: %s\n",aux->str_line);
   // rellenamos los elementos del comando
   // sumamos uno al contador
   len = ft_strlen(aux->str_args[i_pr]);
    element = (char *) malloc (sizeof(char) * (len + 1));
    ft_strnlcpy(element, aux->str_line, pos - 1 , len + 1);
    if (precise_cmp(aux->str_args[i_pr], element, len))
    pos += ++len;
    else
    {
     end = len;
     ft_strnlcpy(aux->str_args[i_pr], element, pos, end);
     if (aux->str_args[i_pr][ft_strlen(aux->str_args[i_pr]) - 1] == '\"'
     || aux->str_args[i_pr][ft_strlen(aux->str_args[i_pr]) - 1] == '\'')
      aux->str_args[i_pr][ft_strlen(aux->str_args[i_pr]) - 1] = '\0';
     pos += ++len;
   }
   free (element);
   i_pr++;
  }
  aux = aux->next;
 }



  //printf ("str_aux: %s\n", aux->str_aux);
  //printf ("str_aux_save: %s\n", aux->str_aux_save);


//utilizamos str_line y str_save para el comando
  //printf ("str_save: %s\n",aux->str_save);
  //char *ft_prepare_aux(char *aux);



 //  while (aux->str_cmd[i_pr])
 //  {
 //   if (aux->str_cmd[i_pr] == '\'' || aux->str_cmd[i_pr] == '\"')
 //   {
 //    printf("el comando %d tiene comillas\n", aux->el_nbr);
 //   }
 //   i_pr++;
 //  }

 //  printf ("%d, %s\n", aux->el_nbr, aux->str_cmd);
 //  aux = aux->next;
 // }
 // free (aux);


 // printf ("%s\n", g_ms->str);
 // printf ("Hola, estoy montando la cadena\n");
 // return ;

}
