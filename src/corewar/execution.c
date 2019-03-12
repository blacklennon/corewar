/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:06:58 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/12 12:32:28 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// debug
#include <stdio.h>

#include <stddef.h>
#include "corewar.h"

static void		read_ocp(t_op *op, uint8_t ocp, t_arguments *args)
{
	t_int_types_enum	*tmp2;
	uint8_t		mask;
	uint8_t		tmp;
	int			i;

	mask = 0xc0;
	i = 0;
	while (i++ < op->nb_params)
	{
		tmp = 0;
		tmp = (tmp & mask) >> (4 - i) * 2;
		if (tmp == REG_CODE && (op->params[i - 1] & T_REG) != 0)
			*tmp2 = int_8;
		else if (tmp == IND_CODE && (op->params[i - 1] & T_IND) != 0)
			*tmp2 = int_16;
		else if (tmp == DIR_CODE && (op->params[i - 1] & T_DIR) != 0)
			*tmp2 = op->little_dir == 1 ? int_16 : int_32;
		else
			crash("bad ocp");
		mask >> 2;
		//TODO find a way to iterate through argument types
	}
}

static void	do_op(t_process *process, t_vm *vm)
{
	uint8_t		op_code;
	uint8_t		ocp;
	t_arguments	args;

	op_code = vm->memory[process->program_counter];
	if (op_tab[op_code].ocp == 1)
		ocp = vm->memory[(process->program_counter + 1) % MEM_SIZE];
	
	if (op_code > 0 && op_code < 17)
		vm->op_table[op_code](process, vm);
	else
		process->next_op++;
	return ;
}

void		launch(t_vm *vm)
{
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
			vm->process[i++].program_counter %= MEM_SIZE;
		}
		vm->cycle++;
	}
}