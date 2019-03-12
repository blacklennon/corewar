/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:19:24 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/12 22:41:34 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "corewar.h"

void		mem_dump(uint8_t *p, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if ((i % 64) == 0)
		{
			if (i != 0)
				printf("\n");
			printf("0x%.4zx: ", i);
		}
		printf("%.2x ", *p);
		p++;
		i++;
	}
}

void		crash(t_process *process, char *str)
{
	printf("Process %s crash: %s\n", process->name, str);
	exit(1);
}

int32_t		swap_int32(int32_t value)
{
	value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
	return ((value << 16) | ((value >> 16) & 0xFFFF));
}

int16_t		swap_int16(int16_t value)
{
	return ((int16_t)(value << 8) + ((uint16_t)value >> 8));
}