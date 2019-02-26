/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:19:24 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/26 19:13:02 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
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
				ft_printf("\n");
			ft_putstr("0x");
			ft_printf("%.4zx : ", i);
		}
		ft_printf("%.2x ", *p);
		p++;
		i++;
	}
}

uint32_t swap_uint32(uint32_t value)
{
	value = ((value << 8) & 0xFF00FF00 ) | ((value >> 8) & 0xFF00FF ); 
	return (value << 16) | (value >> 16);
}