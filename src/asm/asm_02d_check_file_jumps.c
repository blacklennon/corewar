/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_02d_check_file_jumps.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:27:54 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 15:09:58 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

char	*jump_before_header(char *file)
{
	while (file && *file && ft_isspace(*file))
		file++;
	if (*file != NAME_CMD_STRING[0] || *file != NAME_CMD_STRING[0])
		return (NULL);
	return (file);
}

char	*jump_tabspace(char *file)
{
	while (*file && (*file == ' ' || *file == '\t'))
		file++;
	return (file);
}

char	*goto_param(char *file, t_op *op)
{
	file = jump_tabspace(file);
	if (ft_strjstr(file, op->name) != file)
		return (NULL);
	file += ft_strlen(op->name);
	return (file);
}

char	*jump_current_param(char *file, char *max_index)
{
	while (!ft_strchr(" \t,", *file) && file < max_index)
		file++;
	while (ft_strchr(" \t", *file) && file < max_index)
		file++;
	return (file);
}

char	*jump_header(char *file)
{
	if (!file)
		return (NULL);
	if (ft_strjstr(file, COMMENT_CMD_STRING) < ft_strstr(file, \
		NAME_CMD_STRING))
		file = ft_strjstr(file, NAME_CMD_STRING);
	else
		file = ft_strjstr(file, COMMENT_CMD_STRING);
	file = ft_strchr(&file[where_is(file, '"') + 1], '"') + 1;
	file = jump_spaces(file);
	if (!(*file))
		return (NULL);
	return (file);
}
