/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_04_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:06:58 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/05 20:55:13 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "corewar.h"

static void		read_op(t_process *process, t_vm *vm)
{
	uint8_t		op_code;

	process->program_counter %= MEM_SIZE;
	op_code = (uint8_t)read1_memory(vm, process->program_counter);
	if (op_code < LIVE || op_code > AFF)
	{
		process->program_counter++;
		process->next_op = NULL;
		process->do_op = vm->cycle + 1;
		return ;
	}
	process->next_op = &g_op_tab[op_code];
	process->do_op = vm->cycle + g_op_tab[op_code].cycles;
}

static void		do_op(t_process *p, t_vm *vm)
{
	uint16_t	pc;
	t_op		*op;
	t_args		args;

	op = p->next_op;
	if (op != NULL)
	{
		pc = read_args(op, p, &args, vm);
		if (vm->verbose >= 2)
			ft_printf("Player %d is doing %s\n", p->champion->id, op->name);
		if (args.false_ocp == 0 && args.false_reg == 0)
			op->func(p, &args);
		if (op->code != ZJMP || p->carry == 0)
			p->program_counter = pc;
		if (op->code == FORK || op->code == LFORK)
			read_op(vm->process, vm);
	}
	read_op(p, vm);
}

void			launch(t_vm *vm)
{
	t_process	*current_process;

	current_process = vm->process;
	while (current_process != NULL)
	{
		read_op(current_process, vm);
		current_process = current_process->next;
	}
	while (42)
	{
		vm->cycle++;
		if (vm->cycle == vm->cycle_to_check || vm->cycle == vm->cycle_limit)
		{
			if (check_is_alive(vm) == 0 || vm->cycle == vm->cycle_limit)
				break ;
			vm->cycle_to_check += vm->size_cycle;
		}
		current_process = vm->process;
		while (current_process != NULL)
		{
			if (current_process->do_op == vm->cycle)
				do_op(current_process, vm);
			current_process = current_process->next;
		}
	}
}
