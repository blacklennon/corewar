/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_02c_check_name_and_header.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:48:31 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 15:09:46 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

char	*check_head(char *file, int *who, int max_length)
{
	file++;
	if (!(file = jump_str_declar(file, max_length)))
		return (NULL);
	if (*(file = jump_tabspace(file)) != '\n')
		return (0);
	*who = 1;
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
		if ((ft_strjstr_line(file, NAME_CMD_STRING) == file && !name\
			&& !(file = check_head(file, &name, PROG_NAME_LENGTH))))
			return (0);
		else if ((ft_strjstr_line(file, COMMENT_CMD_STRING) == file\
			&& !comment) && !(file = check_head(file, &comment,\
				COMMENT_LENGTH)))
			return (0);
		else if (!ft_isspace(*file) && (!comment || !name))
			return (0);
		if (*(file = jump_tabspace(file)) != '\n')
			return (0);
		if (comment && name)
			break ;
		file++;
	}
	return (1);
}
