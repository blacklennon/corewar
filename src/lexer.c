/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:32:33 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/17 15:49:02 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "op.h"
#include "parser.h"

enum e_lexemes {
	COMMENT,
	LIVE,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF,
	LABEL,
	DIRECT,
	SEPARATOR,
	NAME,
	COMMENT,
}

int		parse_line(char *line, t_asm *env)
{
	while (*line)
	{
		
		line++;
	}
}

void	next(char *input_buffer, t_asm *env)
{
	char	*forward_pointer;
	char	*back_pointer;
	t_op	*op;

	op = g_op_tab;
	forward_pointer = input_buffer;
	back_pointer = input_buffer;
	while (*forward_pointer)
	{
		while (ft_isspace(*forward_pointer))
		{
			forward_pointer++;
			back_pointer++;
		}
	}
}