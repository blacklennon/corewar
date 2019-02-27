/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/27 20:33:07 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "corewar.h"

//WIP

void		live(t_process *process, t_vm *vm)
{
	uint32_t	*arg;
	uint32_t	tmp;

	arg = (uint32_t*)&vm->memory[++process->program_counter];
	tmp = swap_uint32(*arg);
	if (tmp > 0 && tmp <= vm->nb_champs)
		vm->process[(tmp) - 1].live_counter++;
	printf("player %d is alive\n", tmp);
	process->program_counter += 4;
	process->next_op = vm->cycle + 10;
}

void		ld(t_process *process, t_vm *vm)
{
	process->next_op = vm->cycle + 5;
}