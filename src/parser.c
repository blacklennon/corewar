/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:07:17 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/23 15:40:53 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "op.h"
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
	while (*line && *line != '"')
		line++;
	if (*line != '"' || (size = line - tmp) > buf_size)
		return (1);
	while (ft_isspace(*line))
		line++;
	if (*line)
		return (1);
	ft_strncpy(buf_dest, tmp, size);
	return (0);
}

int			parse_label(char *line, t_label **label_listp, size_t index)
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
		create_label(ft_strdup(tmp), index, label_listp);
		*line = LABEL_CHAR;
		return (0);
	}
	return (1);
}

t_arg_type		find_arg_type(char *line)
{
	if (*line == 'r')
		return (T_REG);
	else if (*line == DIRECT_CHAR)
		return (T_DIR);
	else
		return (T_IND);
}

int				parse_arguments(char *line, t_op *op, t_instruction *instruction, t_label *label_list)
{
	t_arg_type	arg_type;
	int		value;
	t_label	*tmp;
	int		n_arg;
	int		offset;

	n_arg = 0;
	offset = 1;
	while (n_arg < op->nb_params)
	{
		arg_type = find_arg_type(line);
		if (!(arg_type & op->params[n_arg]))
		{
			printf("pas le bon argument pour cet opcode | %s\n", line);
			return (1);
		}
		else{
			printf("ca a amrche lol | %s\n", line);
		}
		if (op->ocp)
		{
			instruction->buffer[1] = arg_type << ((MAX_ARGS_NUMBER - n_arg - 1) * 2);
			offset++;
		}
		line++;
		if (*line == LABEL_CHAR && arg_type != T_REG)
		{
			line++;
			if ((tmp = find_label(line, label_list)))
			{
				value = tmp->index;
				line += ft_strlen(tmp->name);
			}
		}
		else
			value = ft_atoi(line);
		while (ft_isdigit(*line))
			line++;
		instruction->buffer[offset + n_arg] = value;
		line++;
		n_arg++;
	}
	return (0);
}

t_op		*parse_operation(char *line)
{
	t_op	*op;
	char	*tmp;

	op = g_op_tab;
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
			*tmp = ' ';
			return (op);
		}
		op++;
	}
	*tmp = ' ';
	return (NULL);
}

int			parse_instruction(char *line, t_asm *env)
{
	int				ret;
	t_op			*op;
	t_instruction	instruction;

	ret = 0;
	init_instruction(&instruction);
	if (!parse_label(line, &env->label_list, env->index))
	{
		while (*line && *line != LABEL_CHAR)
			line++;
		if (*line == LABEL_CHAR)
			line++;
	}
	if ((op = parse_operation(line)))
	{
		line += ft_strlen(op->name);
		while (ft_isspace(*line))
			line++;
		instruction.buffer[0] = op->code;
		ret = parse_arguments(line, op, &instruction, env->label_list);
	}
	else
		return (1);
	return (ret);
}

int		parse_line(char *line, t_asm *env)
{
	int				ret;

	ret = 0;
	while (ft_isspace(*line))
		line++;
	if (!(*line))
		return (0);
	if (!ft_strncmp(line, NAME_CMD_STRING, NAME_CMD_STR_LENGTH))
		ret = parse_string(line + NAME_CMD_STR_LENGTH, env->header.prog_name, PROG_NAME_LENGTH);
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, COMMENT_CMD_STR_LENGTH))
		ret = parse_string(line + COMMENT_CMD_STR_LENGTH, env->header.comment, COMMENT_LENGTH);
	else
		ret = parse_instruction(line, env);
	return (ret);
}