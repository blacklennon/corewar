/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_04_translate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:48:31 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 18:31:03 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

uint8_t		*add_data(char **param, t_binary *bin, int i_op_tab, char **data)
{
	int		i;
	int		value;
	size_t	b_bytes;

	b_bytes = bin->size - g_op_tab[i_op_tab].ocp;
	i = 0;
	while (param[i])
	{
		value = get_right_value(param, i, data, b_bytes);
		if (param[i][0] == DIRECT_CHAR)
			bin->table = add_dir(value, g_op_tab[i_op_tab].little_dir, bin);
		else if (param[i][0] == LABEL_CHAR || (ft_isdigit(param[i][0])\
			|| (param[i][0] == '-' && ft_isdigit(param[i][1]))))
			bin->table = add_ind(value, bin);
		else if (param[i][0] == 'r' && ft_atoi(&param[i][1]) <= REG_NUMBER)
			bin->table = add_byte((uint8_t)ft_atoi(&param[i][1]), bin);
		else
		{
			free(bin->table);
			return (NULL);
		}
		i++;
	}
	return (bin->table);
}

int			clean_param(char **param, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (param[i])
	{
		if (!*(tmp = ft_strtrim(param[i])))
			free(str);
		free(param[i]);
		param[i] = tmp;
		i++;
	}
	return (i);
}

void		*free_param(char **param)
{
	int	i;

	i = 0;
	while (param[i])
		free(param[i++]);
	free(param);
	return (NULL);
}

uint8_t		*get_param_value(char **param, int i_op_tab, t_binary *bin)
{
	int	value;

	if (!g_op_tab[i_op_tab].ocp)
		return (bin->table);
	if (!(value = param_encode(param)))
		return (NULL);
	bin->table = add_byte((value\
		<< (8 - g_op_tab[i_op_tab].nb_params * 2)), bin);
	return (bin->table);
}

uint8_t		*add_param(char *str, int i_op_tab, t_binary *bin, char **data)
{
	char	*clean;
	char	**param;

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
	clean_param(param, str);
	bin->table = get_param_value(param, i_op_tab, bin);
	bin->table = add_data(param, bin, i_op_tab, data);
	free_param(param);
	return (bin->table);
}
