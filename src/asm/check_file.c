/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:23:56 by llopez            #+#    #+#             */
/*   Updated: 2019/04/08 19:05:50 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

void	delete_comment(char *str)
{
	while (*str)
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

int		check_name_comment(char *file)
{
	int		i;
	int		name;
	int		comment;

	i = 0;
	name = 0;
	comment = 0;
	while (file[i])
	{
		if (ft_strstr(&file[i], NAME_CMD_STRING))
		{
			if (name)
				return (0);
			name = 1;
			if (where_is(ft_strchr(&file[i], '"') + 1, '"') >= PROG_NAME_LENGTH)
				return (0);
		}
		else if (ft_strstr(&file[i], COMMENT_CMD_STRING))
		{
			if (comment)
				return (0);
			comment = 1;
			if (where_is(ft_strchr(&file[i], '"') + 1, '"') >= COMMENT_LENGTH)
				return (0);
		}
		while (file[i] != '\n')
			i++;
		i++;
	}
	return (1);
}

int		check_file(char *file)
{
	int		i;

	i = 0;
	delete_comment(file);
	if (!check_name_comment(file))
		return (0);
	return (1);
}
