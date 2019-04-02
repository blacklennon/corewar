/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_04_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:06:58 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/02 18:09:15 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "corewar.h"

static int		parse_ocp(t_op *op, uint8_t ocp, t_args *args)
{
	uint8_t		tmp;
	uint8_t		mask;
	size_t		i;

	mask = 0xc0;
	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		tmp = (ocp & mask) >> ((3 - i) * 2);
		if (tmp == REG_CODE && (op->params[i] & T_REG) != 0)
			args->type[i] = e_reg;
		else if (tmp == IND_CODE && (op->params[i] & T_IND) != 0)
			args->type[i] = e_ind;
		else if (tmp == DIR_CODE && (op->params[i] & T_DIR) != 0)
			args->type[i] = e_dir;
		else if (tmp == 0 && op->params[i] == 0)
			;
		else
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
	args->false_ocp = 0;
	args->false_reg = 0;
	if (op->ocp == 1)
	{
		ocp = read1_memory(vm, pc++);
		if (parse_ocp(op, ocp, args) == 0)
		{
			args->false_ocp = 1;
			if (vm->verbose == 3)
				ft_printf("bad ocp: %d, going to the next operation.\n", ocp);
			return (pc); // donc un cran apres l ocp
			//	crash(process, "bad ocp"); // DEPRECIATED
		}
		while (i < op->nb_params)
		{
			if (args->type[i] == e_reg)
			{
				args->value[i].u_reg = read1_memory(vm, pc++) - 1;
				if (args->value[i].u_reg < 0 || args->value[i].u_reg >= REG_NUMBER)
				{
					args->false_reg = 1;
					if (vm->verbose == 3)
						ft_printf("bad registrer number: %d, going to the next operation.\n", args->value[i].u_reg);
					return (pc); // 
				//	crash(process, "invalid register"); // DEPRECIATED
				}
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
		}
	}
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

static void		do_op(t_process *process, t_vm *vm)
{
	uint16_t	pc;
	t_op		*op;
	t_args		args;

	op = process->next_op;
	if (op != NULL)
	{
		pc = read_args(op, process, &args, vm);
		if (vm->verbose >= 2)
			ft_printf("Player %d is doing %s\n", process->champion->id, op->name);
		if (args.false_ocp == 0 && args.false_reg == 0) // ajout de la condition, les registres et les ocp doivent etre bons pour executer l operation
			op->func(process, &args);
		if (op->code != ZJMP || process->carry == 0)
			process->program_counter = pc;
		if (op->code == FORK || op->code == LFORK)
			read_op(vm->process, vm);
	}
	read_op(process, vm);
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
