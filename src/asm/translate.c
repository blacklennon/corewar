/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:48:31 by llopez            #+#    #+#             */
/*   Updated: 2019/04/04 17:36:34 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

uint8_t		*add_byte(uint8_t content, t_binary *bin)
{
	size_t	i;
	uint8_t	*tmp;

	i = 0;
	tmp = (uint8_t *)malloc(sizeof(uint8_t) * (bin->size + 1));
	while (i < bin->size && bin->table)
	{
		tmp[i] = bin->table[i];
		i++;
	}
	bin->size++;
	tmp[i] = content;
	free(bin->table);
	return (tmp);
}

uint8_t		param_encode(char **param)
{
	int	i;
	uint8_t	content;

	content = 0x0;
	i = 0;
	while (param[i])
	{
		if (param[i][0] == DIRECT_CHAR)
			content |= DIR_CODE;
		else if (ft_isdigit(param[i][0]) || (param[i][0] == '-'\
					&& ft_isdigit(param[i][1])))
			content |= IND_CODE;
		else if (param[i][0] == 'r' && ft_atoi(&param[i][1]) <= REG_NUMBER)
			content |= REG_CODE;
		i++;
		if (param[i])
			content = content << 2;
	}
	return (content);
}

uint8_t		*add_data(char **param, t_binary *bin, int i_op_tab, char **data)
{
	int		i;
	int		value;

	value = 0;
	i = 0;
	while (param[i])
	{
		if (param[i][0] == DIRECT_CHAR)
		{
			if (param[i][1] == LABEL_CHAR)
			{
				value = (where_is(&param[i][1], ',') > 0) ?\
			label_pos(ft_strsub(param[i], 2, where_is(&param[i][1], ',')), data, bin) : \
			label_pos(ft_strsub(param[i], 2, ft_strlen(param[i]) - 2), data, bin);
				printf("\t\033[44m full value : %d \033[0m\n", value - (int)bin->size);
			}
			else
				value = ft_atoi(&param[i][1]);
			if (!op_tab[i_op_tab].little_dir)
			{
				bin->table = add_byte((value & 0xFF000000) >> 24, bin);
				bin->table = add_byte((value & 0x00FF0000) >> 16, bin);
			}
			bin->table = add_byte((value & 0x0000FF00) >> 8, bin);
			bin->table = add_byte((value & 0x000000FF), bin);
		}
		if (ft_isdigit(param[i][0]) || (param[i][0] == '-'\
					&& ft_isdigit(param[i][1])))
		{
			value = ft_atoi(param[i]);
			bin->table = add_byte((value & 0xFF00) >> 8, bin);
			bin->table = add_byte((value & 0x00FF), bin);
		}
		if (param[i][0] == 'r' && ft_atoi(&param[i][1]) <= REG_NUMBER)
			bin->table = add_byte((uint8_t)ft_atoi(&param[i][1]), bin);
		i++;
	}
	return (bin->table);
}

uint8_t		*add_param(char	*str, int i_op_tab, t_binary *bin, char **data)
{
	int	i;
	char	*clean;
	char	**param;
	char	*tmp;

	i = 0;
	str = ft_strjstr(str, op_tab[i_op_tab].name);
	str += ft_strlen(op_tab[i_op_tab].name) + 1;
	clean = ft_strtrim(str);
	param = ft_strsplit(clean, ',');
	free(clean);
	while (param[i])
	{
		tmp = ft_strtrim(param[i]);
		free(param[i]);
		param[i] = tmp;
		i++;
	}
	if (i-1 > op_tab[i_op_tab].nb_params)
	{
		i = 0;
		while (param[i])
			free(param[i++]);
		return (bin->table);
	}
	if (op_tab[i_op_tab].ocp)
		bin->table = add_byte((param_encode(param) << \
			(8 - op_tab[i_op_tab].nb_params * 2)), bin);
	bin->table = add_data(param, bin, i_op_tab, data);
	i = 0;
	while (param[i])
		free(param[i++]);
	free(param);
	return (bin->table);
}
