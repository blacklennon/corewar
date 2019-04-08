/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:48:31 by llopez            #+#    #+#             */
/*   Updated: 2019/04/08 19:26:16 by pcarles          ###   ########.fr       */
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
	tmp = (uint8_t *)ft_memalloc(sizeof(uint8_t) * (bin->size + 1));
	while (i < bin->size && bin->table)
	{
		tmp[i] = bin->table[i];
		i++;
	}
	bin->size++;
	tmp[i] = content;
	i = 0;
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
		else
			return (0);
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
	size_t	b_bytes;

	b_bytes = bin->size - g_op_tab[i_op_tab].ocp;
	value = 0;
	i = 0;
	while (param[i])
	{
		if (param[i][0] == DIRECT_CHAR)
		{
			if (param[i][1] == LABEL_CHAR)
			{
				value = label_pos(param[i], data);
				if (value == -1)
					return (NULL);
				value -= (int)b_bytes;
			}
			else
				value = ft_atoi(&param[i][1]);
			if (!g_op_tab[i_op_tab].little_dir)
			{
				bin->table = add_byte((value & 0xFF000000) >> 24, bin);
				bin->table = add_byte((value & 0x00FF0000) >> 16, bin);
			}
			bin->table = add_byte((value & 0x0000FF00) >> 8, bin);
			bin->table = add_byte((value & 0x000000FF), bin);
		}
		else if (ft_isdigit(param[i][0]) || (param[i][0] == '-'\
					&& ft_isdigit(param[i][1])))
		{
			value = ft_atoi(param[i]);
			bin->table = add_byte((value & 0xFF00) >> 8, bin);
			bin->table = add_byte((value & 0x00FF), bin);
		}
		else if (param[i][0] == 'r' && ft_atoi(&param[i][1]) <= REG_NUMBER)
			bin->table = add_byte((uint8_t)ft_atoi(&param[i][1]), bin);
		else
			return (NULL);
		i++;
	}
	return (bin->table);
}

uint8_t		*add_param(char	*str, int i_op_tab, t_binary *bin, char **data)
{
	int		i;
	char	*clean;
	char	**param;
	char	*tmp;
	uint8_t	*tab_tmp;
	uint8_t	value;

	value = 0x0;
	tab_tmp = NULL;
	i = 0;
	clean = NULL;
	if (!(str = ft_strjstr(str, g_op_tab[i_op_tab].name))\
			|| !(str += ft_strlen(g_op_tab[i_op_tab].name) + 1)\
			|| !(clean = ft_strtrim(str))\
			|| !(param = ft_strsplit(clean, ',')))
	{
		free(str);
		free(clean);
		return (NULL);
	}
	free(clean);
	while (param[i])
	{
		if (!(tmp = ft_strtrim(param[i])))
		{
			free(str);
			return (NULL);
		}
		free(param[i]);
		param[i] = tmp;
		i++;
	}
	if (i-1 > g_op_tab[i_op_tab].nb_params)
	{
		i = 0;
		while (param[i])
			free(param[i++]);
		return (NULL);
	}
	if (g_op_tab[i_op_tab].ocp)
	{
		if (!(value = param_encode(param)))
			return (NULL);
		bin->table = add_byte((value << \
			(8 - g_op_tab[i_op_tab].nb_params * 2)), bin);
	}
	bin->table = add_data(param, bin, i_op_tab, data);
	i = 0;
	while (param[i])
		free(param[i++]);
	free(param);
	return (bin->table);
}
