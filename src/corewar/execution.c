/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:06:58 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/27 14:21:29 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "corewar.h"

void		do_op(t_process *process, t_vm *vm)
{
	uint8_t	op_code;

	op_code = vm->memory[process->program_counter];
}

void		do_cycle(t_vm *vm)
{
	size_t	i;

	i = 0;
	while (42)
	{
		while (i < MAX_PLAYERS)
		{
			if (vm->process[i].next_op == vm->cycle)
				do_op(&vm->process[i], vm);
			i++;
		}
		vm->cycle++;
	}
}