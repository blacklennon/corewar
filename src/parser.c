/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:07:17 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/15 18:32:33 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "op.h"
#include "label.h"
#include "parser.h"

/*

Toutes les fonctions retournent 1 en cas d'echec et 0 si tout va bien

Enregistrer tous les labels et encoder directement les instructions

*/
extern t_op g_op_tab[17];

int			parse_string(char *line, char *buf_dest, size_t buf_size)
{
	char	*tmp;
	size_t	size;

	while (ft_isspace(*line))
		line++;
	if (*line++ != '"')
		return (1);
	tmp = line;
	while (*line)
	{
		if (*line == '"')
			break ;
		line++;
	}
	if (*line != '"' || (size = line - tmp) > buf_size)
		return (1);
	ft_strncpy(buf_dest, tmp, size);
	return (0);
}

// int			parse_arg(char *line)
// {
// 	char	reg_number;

// 	while (ft_isspace(*line))
// 		line++;
// 	while (*line)
// 	{
// 		if (*line == 'r')
// 		{
// 			line++;
// 			reg_number = ft_atoi(line);
// 		}
// 		else if (*line == DIRECT_CHAR)
// 		{
// 			line++;
// 			if (*line == LABEL_CHAR)
// 			{
// 				line++;
// 				//find_label(*lin)
// 			}
// 		}
			
// 		line++;
// 	}
// }

t_op		*parse_operation(char *line)
{
	t_op	*op;
	char	*tmp;

	op = g_op_tab;
	printf("%s\n", line);
	while (*line && ft_isspace(*line))
		line++;
	tmp = line;
	while (*tmp && !ft_isspace(*tmp))
		tmp++;
	*tmp = '\0';
	while (op->name)
	{
		if (!ft_strcmp(line, op->name))
		{
			return (op);
		}
		op++;
	}
	*tmp = ' ';
	return (NULL);
}

int			parse_label(char *line, t_label **label_listp)
{
	char	*tmp;

	tmp = line;
	while (*line && *line != LABEL_CHAR)
	{
		if (!ft_strchr(LABEL_CHARS, (int)*line))
			return (1);
		line++;
	}
	if (tmp != line && *line == LABEL_CHAR)
	{
		*line = '\0';
		create_label(ft_strdup(tmp), 0, label_listp);
		*line = LABEL_CHAR;
		return (0);
	}
	return (1);
}

int			parse_instruction(char *line, t_instruction *instruction, t_label **label_listp)
{
	int		ret;
	t_op	*op;

	ret = 0;
	if (!parse_label(line, label_listp))
	{
		while (*line && *line != LABEL_CHAR)
			line++;
		if (*line == LABEL_CHAR)
			line++;
	}
	if ((op = parse_operation(line)))
	{
		instruction->buffer[0] = op->code;
		printf("op: %s | %s\n", op->name, op->description);
	}
	return (ret);
}

int		parse_line(char *line, t_header *header, t_label **label_listp)
{
	int				ret;
	t_instruction	current_instruction;

	ret = 0;
	init_instruction(&current_instruction);
	while (ft_isspace(*line))
		line++;
	if (!ft_strncmp(line, NAME_CMD_STRING, NAME_CMD_STR_LENGTH))
		ret += parse_string(line + NAME_CMD_STR_LENGTH, header->prog_name, PROG_NAME_LENGTH);
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, COMMENT_CMD_STR_LENGTH))
		ret += parse_string(line + COMMENT_CMD_STR_LENGTH, header->comment, COMMENT_LENGTH);
	else
		ret += parse_instruction(line, &current_instruction, label_listp);
	return (ret);
}