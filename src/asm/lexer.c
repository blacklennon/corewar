/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:03:49 by macuguen          #+#    #+#             */
/*   Updated: 2019/04/08 19:24:24 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "../../lib/libft/includes/libft.h"

int		ft_ratoi(char const *s)
{
	int		flag;
	int		res;

	flag = 0;
	res = 0;
	if(*s == 'r')
		s++;
	if (*s == '-')
	{
		if (*s == '-')
			flag = 1;
		s++;
	}
	while (*s <= '9' && *s >= '0')
	{
		res *= 10;
		res += *s - '0';
		s++;
	}
	if (flag)
		res = -res;
	return (res);
}

void     addlist_opcode(int type,t_token *token, t_token *token_new)
{
    token_new = ft_memalloc(sizeof(*token)); //protgeger
    token_new->type = type;
    /*
        parcour la list(token)
    */
  while (token->next != NULL)
  {
      token = token->next;
  }
    /*
        ajout de nouveau maillon
    */
   token->next = token_new;
   token_new->next = NULL;
   token_new->prev = token;
}

int     ft_str_is_number(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
            i++;
        else
            return (1);
    }
    return (0);
}

void    save_label(char *data, int arg, char *name_of_label)
{

}

void     addlist(t_token *token, t_token *token_new, int arg, char *data)
{
    token_new = ft_memalloc(sizeof(*token)); //protgeger
    /*
        verif de type pour savoir si valeur a enregister ou char * 
    */
    if (arg == T_LAB)
    {
        token_new->type = LABEL;
        save_label(data, T_LAB, token_new->name_of_label); //repertorier label 0,1,2
        //enregistre la string char *
    }
    else if (arg == T_REG)
    {
        token_new->type = REG;
        token_new->valeur = ft_ratoi(data);
        //enregistre la valeur
    }
    else if (arg == T_DIR)
    {
        token_new->type = DIRECT;
        if (ft_str_is_number(data) == 0)
            token_new->valeur = ft_ratoi(data); //changer le ratoi car dans t_dir pas de r 
        else
            save_label(data, arg, token_new->name_of_label);
        //check si valeur ou label
        // voir T_DIR T_IND et label pour repertorier label 0,1,2
    }
    else if (arg == T_IND)
    {
        token_new->type = INDIRECT;
        if (!ft_str_is_number(data))
            token_new->valeur = ft_ratoi(data);
	else
		save_label(); //repertorier label 0,1,2
        //check si valeur ou label
	}
    /*
        parcour la list(token)
    */
	while (token->next != NULL)
	{
		token = token->next;
	}
    /*
        ajout de nouveau maillon
    */
   token->next = token_new;
   token_new->next = NULL;
   token_new->prev = token;
}

int     is_label(char  *str)
{
    int i;

    i = ft_strlen(str);
    if (str[i - 1] == LABEL_CHAR)
        return (2); //definition de label
    if (str[0] == LABEL_CHAR)
        return (1); //appell de label
    if (str[1] == LABEL_CHAR && str[0] == DIRECT_CHAR)
        return (3); //appell de label dircet
    else
        return (0); //erreur
}

int     tokenisation(int i, char **data, t_token *token, t_token *token_new)
{
    int j;

    j = 1;
    while(j <= 17)
    {
        if (ft_strcmp(data[i], g_op_tab[j].name) == 0)
        {
            //operation
            addlist_opcode(j, token, token_new);
            break ;
        }
        if (is_label(data[i]) == 3 || ft_strchr(data[i], DIRECT_CHAR)) //direct
        {
            //si % et : appelle de label
            addlist(token, token_new, T_DIR, data[i]);
            break ;
        } 
        else if (ft_strchr(data[i], LABEL_CHAR)) //label
        {
            //label argument si appelle de label: 1 si defibition label 2 si aucun label 0
            addlist(token, token_new, T_LAB, data[i]);
            break ;
        }
        else if (ft_str_is_number(data[i]) == 0) //indirect
        {
            //chiffe + atoi
            addlist(token, token_new, T_IND, data[i]);
            break ;
        }
        else if (ft_strchr(data[i], 'r')) // INDIRECT ? fichier exel, fair un atoi special regle pour r te % pour sauvgarder les valeur
        {
            addlist(token, token_new, T_REG, data[i]);
            break ;
        }
        j++;
    }
    if (j == 17)
            return (1);
    return (0);
}

int	lexer(char **data)
{
    int		i;
    t_token	*token;
    t_token	*token_new;

    i = 0;
    token = NULL;
    while (data[i])
    {
        if (tokenisation(i, data, token, token_new) == 1)
            return(-1);
        i++;
    }
    return (0);
}
