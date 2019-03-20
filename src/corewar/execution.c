/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:06:58 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/20 20:00:39 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// debug
#include <stdio.h>

#include <stddef.h>
#include "corewar.h"

// This function read the OCP, and fill up the arg struct, it return 0 if the
// current operation has a bad OCP. (the check is done with the op_tab values)
static int		parse_ocp(t_op *op, uint8_t ocp, t_args *args)
{
	uint8_t		mask;
	uint8_t		tmp;
	int			i;

	mask = 0xc0;
	i = 0;
	while (i < op->nb_params)
	{
		tmp = (ocp & mask) >> ((3 - i) * 2);
		if (tmp == REG_CODE && (op->params[i] & T_REG) != 0)
			args->type[i] = e_reg;
		else if (tmp == IND_CODE && (op->params[i] & T_IND) != 0)
			args->type[i] = e_ind;
		else if (tmp == DIR_CODE && (op->params[i] & T_DIR) != 0)
			args->type[i] = e_dir;
		else
			return (0);
		mask >>= 2;
		i++;
	}
	while (i < MAX_ARGS_NUMBER)
	{
		if ((ocp & mask) >> ((3 - i) * 2) != 0)
			return (0);
		mask >>= 2;
		i++;
	}
	return (1);
}

static uint16_t	read_args(t_op *op, t_process *process, t_args *args, t_vm *vm)
{
	uint8_t		ocp;
	uint16_t	pc;
	int			i;

	i = 0;
	pc = process->program_counter + 1;
	if (op->ocp == 1) // If OCP we parse it and then we read arguments from memory
	{
		ocp = read1_memory(vm, pc++);
		if (parse_ocp(op, ocp, args) == 0)
			crash(process, "bad ocp");
		while (i < op->nb_params)
		{
			if (args->type[i] == e_reg)
			{
				args->value[i].u_reg = read1_memory(vm, pc) - 1;
				if (args->value[i].u_reg < 0 || args->value[i].u_reg >= REG_NUMBER)
					crash(process, "invalid register");
				pc += 1;
			}
			else if (args->type[i] == e_ind)
			{
				args->value[i].u_ind = read2_memory(vm, pc);
				pc += 2;
			}
			else if (args->type[i] == e_dir && op->little_dir == 1)
			{
				args->value[i].u_dir16 = read2_memory(vm, pc);
				pc += 2;
			}
			else if (args->type[i] == e_dir && op->little_dir == 0)
			{
				args->value[i].u_dir32 = read4_memory(vm, pc);
				pc += 4;
			}
			else
				crash(process, "wtf this should never be reached, you can go hang yourself");
			i++;
			// Don't forget to increment program counter correctly
		}
	}
	// special cases, operations with no OCP
	else if (op->params[0] == T_DIR && op->little_dir == 1)
	{
		args->value[0].u_dir16 = read2_memory(vm, pc);
		pc += 2;
	}
	else if (op->params[0] == T_DIR && op->little_dir == 0)
	{
		args->value[0].u_dir32 = read4_memory(vm, pc);
		pc += 4;
	}
	else if (op->params[0] == T_REG)
	{
		args->value[0].u_reg = read1_memory(vm, pc);
		pc += 1;
	}
	else
		crash(process, "wtf this should never be reached, you can go hang yourself");
	return (pc);
}

static void		read_op(t_process *process, t_vm *vm)
{
	uint8_t		op_code;

	op_code = (uint8_t)read1_memory(vm, process->program_counter);
	if (op_code < LIVE || op_code > AFF)
	{
		process->do_op = vm->cycle + 1;
		process->next_op = NULL;
		process->program_counter++;
		printf("Player (%s), bad opcode: 0x%.2x consumming 1 cycle\n", process->name, op_code);
		return ;
	}
	process->next_op = &op_tab[op_code];
	process->do_op = vm->cycle + op_tab[op_code].cycles;
}

static void		do_op(t_process *process, t_op *op, t_vm *vm)
{
	uint16_t	pc;
	t_args		args;

	if (op != NULL)
	{
		printf("Process %s doing op %s\n", process->name, op->name);
		pc = read_args(op, process, &args, vm);
		op->func(process, &args);
		if (op->code != ZJMP || process->carry == 0)
			process->program_counter = pc;
	}
	read_op(process, vm);
}

void			launch(t_vm *vm)
{
	size_t		i;

	i = 0;
	while (i < vm->nb_champs)
	{
		read_op(&vm->process[i], vm);
		i++;
	}
	while (42)
	{
		//printf("\ncylce %zu\n", vm->cycle);
		if (vm->cycle == 500)
			break ;
		// while (vm->fork)
		// {
		// 	vm->fork = vm->fork->next;
		// }
		i = vm->nb_champs;
		while (42)
		{
			if (vm->process[i].do_op == vm->cycle)
				do_op(&vm->process[i], vm->process[i].next_op, vm);
			vm->process[i].program_counter %= MEM_SIZE;
			i--;
			if (i == 0)
				break ;
		}
		vm->cycle++;
	}
}