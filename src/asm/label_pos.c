/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:51:35 by llopez            #+#    #+#             */
/*   Updated: 2019/04/05 18:43:26 by llopez           ###   ########.fr       */
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
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == DIRECT_CHAR)
			size += (op_tab[op].little_dir) ? 2 : 4;
		else if (ft_isdigit(str[i]) || (str[i] == '-'\
					&& ft_isdigit(str[i+1])))
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

int		ft_labelcmp(char *label, char *str)
{
	int	i;

	i = 0;
	while (label[i])
	{
		if (str[i] != label[i])
			return (1);
		i++;
	}
	return (str[i] != LABEL_CHAR);
}

int		label_pos(char *label, char **data)
{
	int		i;
	size_t	distance;

	int	tmp;

	distance = 0;
	i = 0;
	(void)label;
	while (data[i])
	{
		if (!ft_labelcmp(label, data[i]))
			break;
		if (find_op(data[i]))
		{
			printf("%x ", op_tab[find_op(data[i])].code);
			if (op_tab[find_op(data[i])].ocp)
				printf("0 ");
			tmp = 0;
			while (tmp < (int)param_size(data[i]))
			{
				printf("0 ");
				tmp++;
			}
			printf("\n");
			distance += 1 + op_tab[find_op(data[i])].ocp + param_size(data[i]);
		}
		i++;
	}
	distance++;
	//printf("\t\033[41m position %zu \033[0m\n", distance);
	return (distance);
}
