/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:32:33 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/22 18:18:00 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include <errno.h>
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

int			find_label(char *begin_pointer, char *end_pointer)
{
	if (*begin_pointer == LABEL_CHAR)
		begin_pointer++;
	else
		return (end_pointer - begin_pointer);
	while (ft_strchr(LABEL_CHARS, (int)(*begin_pointer)))
		begin_pointer++;
	return (end_pointer - begin_pointer);
}

int32_t		find_value(char *begin_pointer, char *end_pointer)
{
	int32_t	ret;
	long	tmp;

	if (end_pointer - begin_pointer > 10)
	{
		errno = ERANGE;
		return (-1);
	}
	tmp = ft_atol(begin_pointer);
	if (tmp > INT32_MAX || tmp < INT32_MIN)
	{
		errno = ERANGE;
		return (-1);
	}
	ret = (int32_t)tmp;
	return (ret);
}

t_token_type	return_token(char *begin_pointer, char *end_pointer)
{
	t_op	*op;

	op = g_op_tab;
	if (!ft_strncmp(begin_pointer, NAME_CMD_STRING, end_pointer - begin_pointer))
		return (TOKEN_MISC_NAME);
	if (!ft_strncmp(begin_pointer, COMMENT_CMD_STRING, end_pointer - begin_pointer))
		return (TOKEN_MISC_COMMENT);
	while (op->name)
	{
		if (!ft_strncmp(begin_pointer, op->name, end_pointer - begin_pointer))
			return (op->token);
		op++;
	}
	if (!check_label(begin_pointer, end_pointer))
		return (TOKEN_MISC_LABEL);
	return (TOKEN_MISC_UNDEFINED);
}

t_token		*next_token(char *input_buffer)
{
	static char	*forward_pointer;
	char		*back_pointer;
	t_token		*current_token;

	if (!(current_token = new_token()))
		return (NULL);
	if (input_buffer)
		forward_pointer = input_buffer;
	back_pointer = forward_pointer;
	if (!*forward_pointer)
		current_token->type = TOKEN_MISC_EOL;
	while (*forward_pointer)
	{
		while (ft_isspace(*forward_pointer))
			forward_pointer++;
		back_pointer = forward_pointer;
		while (*forward_pointer && !ft_isspace(*forward_pointer) && *forward_pointer != SEPARATOR_CHAR)
			forward_pointer++;
		current_token = return_token(back_pointer, forward_pointer);
	}
	return (current_token);
}

t_token		*new_token(void)
{
	t_token	*new;

	if (!(new = (t_token*)malloc(sizeof(*new))))
		return (NULL);
	new->type = TOKEN_MISC_UNDEFINED;
	new->value = 0;
	new->label = NULL;
	return (new);
}