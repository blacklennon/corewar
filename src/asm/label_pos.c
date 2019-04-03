/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:51:35 by llopez            #+#    #+#             */
/*   Updated: 2019/04/03 16:38:51 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

void	replace_by_space(unsigned int i, char *str)
{
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

int		label_pos(char *label, char **data)
{
	int		i;

	i = 0;
	while (data[i])
	{
		if (where_is(data[i], LABEL_CHAR) >= 0 \
				&& data[i][where_is(data[i], LABEL_CHAR) - 1] != DIRECT_CHAR \
				&& !ft_strncmp(label, data[i], ft_strlen(label)))
		{
			printf("found label %s\n", label);
		}
		i++;
	}
	return (0);
}
