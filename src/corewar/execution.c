/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:06:58 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/28 16:45:42 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// debug
#include <stdio.h>

#include <stddef.h>
#include "corewar.h"

static void	do_op(t_process *process, t_vm *vm)
{
	uint8_t	op_code;

	op_code = vm->memory[process->program_counter];
	if (op_code == 1)
		vm->op_table[op_code](process, vm);
	else
		process->next_op++;
	return ;
}

void		launch(t_vm *vm)
{
	size_t	tmp;
	size_t	i;

	while (42)
	{
		//printf("cycle: %zu\n", vm->cycle);
		if (vm->cycle == 500)
			break ;
		i = 0;
		while (i < vm->nb_champs)
		{
			if (vm->process[i].next_op == vm->cycle)
				do_op(&vm->process[i], vm);
			i++;
		}
		tmp = 0;
		while (tmp < vm->nb_champs)
		{
			printf("player %lu: %zu lives\n", tmp + 1, vm->process[tmp].live_counter);
			if (vm->process[tmp].program_counter >= MEM_SIZE)
				vm->process[tmp].program_counter %= MEM_SIZE;
			tmp++;
		}
		vm->cycle++;
	}
}