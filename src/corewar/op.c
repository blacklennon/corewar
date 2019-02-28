/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/28 17:57:33 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "corewar.h"

//WIP

uint32_t	read_memory(t_vm *vm, size_t index)
{
	uint32_t	*tmp;
	uint8_t		tab[4];
	size_t		i;

	i = 0;
	index %= MEM_SIZE;
	tmp = (uint32_t*)&vm->memory[index];
	if (MEM_SIZE - index > 4)
		return (swap_uint32(*tmp));
	else
	{
		tmp = (uint32_t*)tab;
		while (i < 4)
		{
			tab[i] = vm->memory[index];
			index++;
			i++;
			index %= MEM_SIZE;
		}
		return (swap_uint32(*tmp));
	}
}

void		live(t_process *process, t_vm *vm)
{
	uint32_t	tmp;

	tmp = read_memory(vm, ++process->program_counter);
	if (tmp > 0 && tmp <= vm->nb_champs)
		vm->process[(tmp) - 1].live_counter++;
	printf("player %d is alive\n", tmp);
	process->program_counter += 4;
	process->next_op = vm->cycle + 10;
}

void		zjmp(t_process *process, t_vm *vm)
{
	uint16_t	*arg;

	arg = (uint16_t*)&vm->memory[++process->program_counter];
	process->next_op = vm->cycle + 20;
}

void		ld(t_process *process, t_vm *vm)
{
	process->next_op = vm->cycle + 5;
}