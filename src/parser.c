/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:07:17 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/15 16:24:38 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "libft.h"
#include "op.h"
#include "label.h"
#include "parser.h"

/*

Toutes les fonctions retournent 1 en cas d'echec et 0 si tout va bien

Enregistrer tous les labels et encoder directement les instructions

*/


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
	t_op	op_tab[17] =
	{
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
		{"zjmp", 1, {T_DIR}, 9,	20, "jump if zero", 0, 1},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
		{0, 0, {0}, 0, 0, 0, 0, 0}
	};
	char	*tmp;

	op = op_tab;
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

int			parse_instruction(char *line, t_label **label_listp)
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
		printf("op: %s %s\n", op->name, op->description);
	return (ret);
}

int		parse_line(char *line, t_header *header, t_label **label_listp)
{
	int				ret;
	//t_instruction	current;

	ret = 0;
	while (ft_isspace(*line))
		line++;
	if (!ft_strncmp(line, NAME_CMD_STRING, NAME_CMD_STR_LENGTH))
		ret += parse_string(line + NAME_CMD_STR_LENGTH, header->prog_name, PROG_NAME_LENGTH);
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, COMMENT_CMD_STR_LENGTH))
		ret += parse_string(line + COMMENT_CMD_STR_LENGTH, header->comment, COMMENT_LENGTH);
	else
		ret += parse_instruction(line, label_listp);
	return (ret);
}