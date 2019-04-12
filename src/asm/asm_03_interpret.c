/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:49:49 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 18:27:01 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

int			jump_index_header(char **data)
{
	int	i;
	int	found;

	found = 0;
	i = 0;
	while (data[i])
	{
		if (found == 2)
			break ;
		if ((ft_strjstr(data[i], NAME_CMD_STRING)\
				|| ft_strjstr(data[i], COMMENT_CMD_STRING)))
			found++;
		i++;
	}
	return (i);
}

t_binary	*interpret(char **data)
{
	int			i;
	int			j;
	t_binary	*table;

	table = (t_binary *)ft_memalloc(sizeof(t_binary));
	table->size = 0;
	table->table = NULL;
	i = jump_index_header(data);
	while (data[i])
	{
		j = 1;
		while (j < 17)
		{
			if (ft_strjstr(data[i], g_op_tab[j].name))
			{
				table->table = add_byte(g_op_tab[j].code, table);
				table->table = add_param(data[i], j, table, data);
				break ;
			}
			j++;
		}
		i++;
	}
	return (table);
}
