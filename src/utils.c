/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:24:56 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/09 19:00:31 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int32_t		swap_int32(int32_t value)
{
	value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
	return ((value << 16) | ((value >> 16) & 0xFFFF));
}

int16_t		swap_int16(int16_t value)
{
	return ((int16_t)(value << 8) + ((uint16_t)value >> 8));
}

void		corewar_usage(void)
{
	ft_printf("usage: ./corewar [-d cycle] [-v level] [-n player_number] "
	"file.cor ...\n\n         -d cycle: set a cycle to stop and dump memory of"
	" vm\n         -v level: set verbosity level between 1 and 3\n -n "
	"player_number: force a player to have a specific number\n");
}
