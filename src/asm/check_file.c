/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:23:56 by llopez            #+#    #+#             */
/*   Updated: 2019/04/11 19:54:22 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

int		ft_cbc(char *file, char a, char b)
{
	while (file && *file)
	{
		if (*file == b)
			return (0);
		if (*file == a)
			return (1);
		file++;
	}
	return (0);
}

void	delete_comment(char *str)
{
	while (str && *str)
	{
		if (*str == '#')
		{
			while (*str && *str != '\n')
			{
				*str = ' ';
				str++;
			}
		}
		str++;
	}
}

char	*jump_spaces(char *file)
{
	while (ft_isalnum(*file))
		file++;
	while (ft_isspace(*file))
		file++;
	return (file);
}

char	*jump_str_declar(char *file, int max_size)
{
	int	i;

	if (!file)
		return (0);
	file = jump_spaces(file);
	if (*file != '"')
		return (0);
	i = 1;
	if (!ft_cbc(file + i, '"', '\n'))
		return (0);
	while (*(file + i) && *(file + i) != '"')
		i++;
	if (i + 1 > max_size)
		return (0);
	file += i + 1;
	return (file);
}

char	*check_head(char *file, int *who, int max_length)
{
	file++;
	if (!(file = jump_str_declar(file, max_length)))
		return (NULL);
	*who = 1;
	return (file);
}

char	*jump_before_header(char *file)
{
	while (file && *file && ft_isspace(*file))
		file++;
	if (*file != NAME_CMD_STRING[0] || *file != NAME_CMD_STRING[0])
		return (NULL);
	return (file);
}

int		check_name_comment(char *file)
{
	int		name;
	int		comment;

	name = 0;
	comment = 0;
	if (!(file = jump_before_header(file)))
		return (0);
	while (*file)
	{
		if ((ft_strjstr(file, NAME_CMD_STRING) == file && !name\
					&& !(file = check_head(file, &name, PROG_NAME_LENGTH)))\
				|| ((ft_strjstr(file, COMMENT_CMD_STRING) == file && !comment)\
					&& !(file = check_head(file, &comment, COMMENT_LENGTH)))) 
				return (0);
		else if (!ft_isspace(*file) && (!comment || !name))
			return (0);
		if (comment && name)
			break;
		file++;
	}
	return (1);
}

char	*ft_strjstr_line(char const *str, char const *search)
{
	int i;
	int b;

	b = 0;
	i = 0;
	if (!search || !str)
		return (NULL);
	while (str && str[i])
	{
		b = 0;
		if (str[i] == '\n')
			break;
		while (str[i + b] && search[b] && search[b] == str[i + b])
			b++;
		if ((size_t)b == ft_strlen(search) && ((!i\
						 || ft_isspace(str[i - 1]))\
					 && ft_isspace(str[i + b])))
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

int		find_op_line(char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 1;
	while (i < 17)
	{
		tmp = ft_strjstr_line(str, g_op_tab[i].name);
		if (tmp && tmp < ft_strchr(str, '\n'))
			return (i);
		i++;
	}
	return (0);
}

int		find_label(char *label_name, char *file)
{
	char	*pos;
	int		label_length;

	label_name = ft_strchr(label_name, LABEL_CHAR) + 1;
	label_length = 0;
	while (ft_strchr(LABEL_CHARS, label_name[label_length]))
		label_length++;
	label_name = ft_strsub(label_name, 0, label_length);
	if (!ft_strlen(label_name))
		return (0);
	pos = ft_strstr(file, label_name);
	while (pos && file && pos[ft_strlen(label_name)] != LABEL_CHAR)
	{
		file = pos + ft_strlen(label_name);
		pos = ft_strstr(file, label_name);
	}
	if (pos)
		pos += ft_strlen(label_name);
	free(label_name);
	return ((pos && *pos == LABEL_CHAR));
}

int		ft_valid_number(char *file)
{
	char	*tmp;

	tmp = file;
	if (*file == '-')
		file++;
	while (*file && ft_isdigit(*file))
		file++;
	if ((*file == SEPARATOR_CHAR || *file == COMMENT_CHAR || ft_isspace(*file)) && tmp < file)
		return (1);
	return (0);
}

char	*jump_tabspace(char *file)
{
	while (*file && (*file == ' ' || *file == '\t'))
		file++;
	return (file);
}

int		check_param_code(char *file, int *params_found, char *start, t_op *op)
{
	if (((T_REG & op->params[*params_found]) != 0) && *file == 'r' \
			&& (ft_atoi(file + 1) <= REG_NUMBER\
				&& ft_valid_number(file + 1) && ft_atoi(file + 1) >= 1))
		(*params_found)++;
	else if (((T_IND & op->params[*params_found]) != 0)\
			&& ft_valid_number(file))
		(*params_found)++;
	else if (((T_DIR & op->params[*params_found]) != 0)\
			&& *file == DIRECT_CHAR && (ft_valid_number(file + 1)\
				|| (*(file + 1) == LABEL_CHAR && find_label(file, start))))
		(*params_found)++;
	else if (*file == LABEL_CHAR && (T_IND & op->params[*params_found])\
			&& find_label(file, start))
		(*params_found)++;
	else
		return (0);
	return (1);
}

char	*check_param(int op_code, char *file, char *start)
{
	int		params_found;
	t_op	*op;
	char	*max_index;

	if (!op_code)
		return (0);
	op = &g_op_tab[op_code];
	file = jump_tabspace(file);
	if (ft_strjstr(file, op->name) != file)
		return (0);
	file += ft_strlen(op->name);
	max_index = ft_strchr(file, '\n');
	params_found = 0;
	while (*file && file < max_index)
	{
		while (ft_strchr(" \t", *file) && file < max_index)
			file++;
		if (params_found > op->nb_params - 1\
				|| !check_param_code(file, &params_found, start, op))
			return (0);
		while (!ft_strchr(" \t,", *file) && file < max_index)
			file++;
		while (ft_strchr(" \t", *file) && file < max_index)
			file++;
		if (*file == SEPARATOR_CHAR && file + 1 < max_index)
			file++;
		else
			break;
	}
	if (params_found != op->nb_params)
		return (NULL);
	return (file);
}

char	*jump_header(char *file)
{
	if (ft_strstr(file, COMMENT_CMD_STRING) < ft_strstr(file, \
				NAME_CMD_STRING))
		file = ft_strstr(file, NAME_CMD_STRING);
	else
		file = ft_strstr(file, COMMENT_CMD_STRING);
	file = ft_strchr(&file[where_is(file, '"') + 1], '"') + 1;
	file = jump_spaces(file);
	return (file);
}

int		check_char_label(char *label_name)
{
	int	i;

	i = 0;
	while (label_name[i] && ft_strchr(LABEL_CHARS, label_name[i]))
		i++;
	return ((i == (int)ft_strlen(label_name)));
}

char	*check_label(char *file)
{
	char	*label_name;
	int		i;
	char	*ptr;

	ptr = file;
	i = 0;
	label_name = NULL;
	if (ft_cbc(file, LABEL_CHAR, '\n'))
	{
		while (!ft_strchr(" \n\t:", file[i]))
			i++;
		if (file[i] != LABEL_CHAR)
			return (ptr);
		label_name = ft_strsub(file, 0, where_is(file, LABEL_CHAR));
		if (!ft_strlen(label_name) || !check_char_label(label_name))
		{
			free(label_name);
			return (NULL);
		}
		free(label_name);
		file = ft_strchr(file, LABEL_CHAR) + 1;
	}
	return (file);
}

int		check_all(char *file)
{
	int		line;
	int		i_op_tab;
	char	*start;

	if (!file)
		return (0);
	i_op_tab = 0;
	line = 1;
	start = file;
	file = jump_header(file);
	if (!(*file))
		return (0);
	while (file && *file)
	{
		if (!(file = check_label(file)))
			return (0);
		while (*file == ' ' || *file == '\t')
			file++;
		if (*file == '\n' && file++ && ++line)
			continue;
		if (!(i_op_tab = find_op_line(file))\
				|| !(file = check_param(i_op_tab, file, start)))
			return (0);
		file = jump_tabspace(file);
		if (*file != '\n' && *file)
			return (0);
		file++;
		line++;
	}
	return ((*file) ? 0 : 1);
}

int		check_file(char *file)
{
	if (!file)
		return (0);
	delete_comment(file);
	if (!check_name_comment(file) || !check_all(file))
		return (0);
	return (1);
}
