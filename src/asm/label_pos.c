/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:51:35 by llopez            #+#    #+#             */
/*   Updated: 2019/04/10 23:03:09 by llopez           ###   ########.fr       */
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
		str = ft_strjstr(str, g_op_tab[op].name);
	else
	{
		printf("Err 1\n");
		return (0);
	}
	while (str != ft_strjstr(str, g_op_tab[op].name))
		str++;
	str = jump_spaces(str);
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == DIRECT_CHAR)
			size += (g_op_tab[op].little_dir) ? 2 : 4;
		else if (ft_isdigit(str[i]) || (str[i] == '-'\
					&& ft_isdigit(str[i+1])))
			size += 2;
		else if (str[i] == 'r')
			size++;
		else if (str[i] == LABEL_CHAR)
			size += 2;
		else
		{
			printf("Err 2\n");
			return (0);
		}
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
		if (ft_strjstr(str, g_op_tab[i].name))
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

int		label_pos(char *param, char **data)
{
	int		i;
	size_t	distance;
	char	*label;

	distance = 0;
	i = 0;
	if (param[0] == DIRECT_CHAR)
		label = (where_is(&param[1], ',') > 0) ? ft_strsub(param, 2,\
			where_is(&param[1], ',')) : ft_strsub(param, 2, \
			ft_strlen(param) - 2);
	else
		label = (where_is(&param[1], ',') > 0) ? ft_strsub(param, 1,\
			where_is(&param[1], ',')) : ft_strsub(param, 1, \
			ft_strlen(param) - 1);
	while (data[i])
	{
		printf("%s\n", data[i]);
		if (!ft_labelcmp(label, data[i]))
			break;
		if (find_op(data[i]))
			distance += 1 + g_op_tab[find_op(data[i])].ocp + param_size(data[i]);
		if (find_op(data[i]) && !param_size(data[i]))
		{
			printf("error in param line %d\n", i);
			return (-1);
		}
		i++;
	}
	distance++;
	free(label);
	return (distance);
}
