/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_02b_check_params_and_labels.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:11:44 by jdouniol          #+#    #+#             */
/*   Updated: 2019/04/12 12:53:47 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "common.h"
#include "op.h"
#include "asm.h"

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
	if (!(file = goto_param(file, op)))
		return (NULL);
	max_index = ft_strchr(file, '\n');
	params_found = 0;
	while (*file && file < max_index)
	{
		while (ft_strchr(" \t", *file) && file < max_index)
			file++;
		if (params_found > op->nb_params - 1\
				|| !check_param_code(file, &params_found, start, op))
			return (0);
		file = jump_current_param(file, max_index);
		if (*file == SEPARATOR_CHAR && file + 1 < max_index)
			file++;
		else
			break ;
	}
	return ((params_found != op->nb_params) ? NULL : file);
}
