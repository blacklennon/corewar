/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:06:58 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/27 16:22:27 by pcarles          ###   ########.fr       */
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
		vm->op_table[op_code];
	else
	{
		printf("shit\n");
	}
	
}

void		launch(t_vm *vm)
{
	size_t	i;

	while (42)
	{
		i = 0;
		if (vm->cycle == 500)
			break ;
		while (i < vm->nb_champs)
		{
			if (vm->process[i].next_op == vm->cycle)
				do_op(&vm->process[i], vm);
			i++;
		}
		vm->cycle++;
	}
}