/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:51:35 by llopez            #+#    #+#             */
/*   Updated: 2019/04/05 15:09:39 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

size_t	param_size(char *str)
{
	int		i;
	int		op;
	size_t	size;

	i = 0;
	size = 0;
	if ((op = find_op(str)))
	{
		str = ft_strjstr(str, op_tab[op].name);
		str += ft_strlen(op_tab[op].name);
	}
	else
		return (0);
	while (*str == ' ' || *str == '\t')
		str++;
	while (str[i])
	{
		if (str[i] == DIRECT_CHAR)
			size += (op_tab[op].little_dir) ? 2 : 4;
		else if (ft_isdigit(str[i]) || (str[i] == '-'\
					&& ft_isdigit(str[i])))
			size += 2;
		else if (str[i] == 'r')
			size++;
		while (str[i] && str[i] != ',')
			i++;
		i += (str[i] == ',') ? 1 : 0;
	}
	return (size);
}

int		find_op(char *str)
{
	int i;

	i = 1;
	while (i < 17)
	{
		if (ft_strjstr(str, op_tab[i].name))
			return (i);
		i++;
	}
	return (0);
}

int		label_pos(char *label, char **data)
{
	int		i;
	size_t	distance;

	distance = 0;
	i = 0;
	while (data[i])
	{
		if (where_is(data[i], LABEL_CHAR) >= 0 \
				&& !ft_strncmp(label, data[i], ft_strlen(label)))
			break;
		if (find_op(data[i]))
			distance += 1 + op_tab[find_op(data[i])].ocp + param_size(data[i]);
		i++;
	}
	return (distance);
}
