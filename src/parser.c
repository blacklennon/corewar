/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:07:17 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/11 20:06:44 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "op.h"
#include "label.h"
#include "parser.h"

/*

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
	if (*line != '"' || (size = tmp - line) > buf_size)
		return (1);
	ft_strncpy(buf_dest, tmp, size);
	return (0);
}

int			parse_arg(char *line)
{
	char	reg_number;

	while (ft_isspace(*line))
		line++;
	while (*line)
	{
		if (*line == 'r')
		{
			line++;
			reg_number = ft_atoi(line);
		}
		else if (*line == DIRECT_CHAR)
		{
			line++;
			if (*line == LABEL_CHAR)
			{
				line++;
				//find_label(*lin)
			}
		}
			
		line++;
	}
}

t_op		*parse_operation(char *line)
{
	t_op	*op;

	while (op->name)
	{
		if (!ft_strncmp(line, op->name, ft_strlen(op->name)))
			return (op);
		op++;
	}
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
	char	*tmp;

	parse_label(line, label_listp);
	parse_operation(line);
}

int		parse_line(char *line, t_header *header)
{
	int				ret;
	t_instruction	current;

	ret = 0;
	while (ft_isspace(*line))
		line++;
	if (!ft_strncmp(line, NAME_CMD_STRING, 5))
		ret += parse_string(line, header->prog_name, PROG_NAME_LENGTH);
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 5))
		ret += parse_string(line, header->comment, COMMENT_LENGTH);
	return (ret);
}