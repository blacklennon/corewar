/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:49:49 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 12:38:00 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

t_binary	*interpret(char **data)
{
	int			i;
	int			j;
	t_binary	*table;

	table = (t_binary *)ft_memalloc(sizeof(t_binary));
	table->size = 0;
	table->table = NULL;
	i = 0;
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
