/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_02a_check_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:23:56 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 13:04:17 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

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
			break ;
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

int		ft_valid_number(char *file)
{
	char	*tmp;

	tmp = file;
	if (*file == '-')
		file++;
	while (*file && ft_isdigit(*file))
		file++;
	if ((*file == SEPARATOR_CHAR || *file == COMMENT_CHAR || ft_isspace(*file))\
			&& tmp < file)
		return (1);
	return (0);
}

int		check_all(char *file)
{
	int		i_op_tab;
	char	*start;

	i_op_tab = 0;
	start = file;
	if (!(file = jump_header(file)))
		return (0);
	while (file && *file)
	{
		if (!(file = check_label(file)))
			return (0);
		file = jump_tabspace(file);
		if (*file == '\n' && file++)
			continue;
		if (!(i_op_tab = find_op_line(file))\
				|| !(file = check_param(i_op_tab, file, start)))
			return (0);
		file = jump_tabspace(file);
		if (*file != '\n' && *file)
			return (0);
		file++;
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
