/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:32:33 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/18 19:03:59 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "op.h"
#include "parser.h"

extern t_op g_op_tab[17];

int			check_label(char *begin_pointer, char *end_pointer)
{
	while (ft_strchr(LABEL_CHARS, (int)(*begin_pointer)))
		begin_pointer++;
	if (*begin_pointer == LABEL_CHAR)
		begin_pointer++;
	return (end_pointer - begin_pointer);
}

int			check_label_call(char *begin_pointer, char *end_pointer)
{
	if (*begin_pointer == LABEL_CHAR)
		begin_pointer++;
	while (ft_strchr(LABEL_CHARS, (int)(*begin_pointer)))
		begin_pointer++;
	return (end_pointer - begin_pointer);
}

t_token		return_token(char *begin_pointer, char *end_pointer)
{
	t_op	*op;

	op = g_op_tab;
	if (!ft_strncmp(begin_pointer, NAME_CMD_STRING, end_pointer - begin_pointer))
		return (NAME);
	if (!ft_strncmp(begin_pointer, COMMENT_CMD_STRING, end_pointer - begin_pointer))
		return (COMMENT);
	while (op->name)
	{
		if (!ft_strncmp(begin_pointer, op->name, end_pointer - begin_pointer))
			return (op->token);
		op++;
	}
	if (!check_label(begin_pointer, end_pointer))
		return (LABEL);
	return (UNDEFINED);
}

void		next(char *input_buffer)
{
	char	*forward_pointer;
	char	*back_pointer;
	t_token	current_token;

	forward_pointer = input_buffer;
	back_pointer = input_buffer;
	while (*forward_pointer)
	{
		while (ft_isspace(*forward_pointer))
			forward_pointer++;
		back_pointer = forward_pointer;
		while (*forward_pointer && !ft_isspace(*forward_pointer))
			forward_pointer++;
		if ((current_token = return_token(back_pointer, forward_pointer)) == UNDEFINED)
			return ;
		back_pointer = forward_pointer;
	}
}