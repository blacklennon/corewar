/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/26 19:35:43 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "corewar.h"

void		get_value_of_arg(t_process *process, t_int_types *value, \
			t_int_types_enum *type, int opcode)
{
	if (*type == e_reg)
		(*value).u_dir32 = process->registers[(*value).u_reg];
	else if (*type == e_ind && (opcode == LLD || opcode == LLDI))
		(*value).u_dir32 = read4_memory(get_vm(NULL), \
				process->program_counter + (*value).u_ind);
	else if (*type == e_ind)
		(*value).u_dir32 = read4_memory(get_vm(NULL), \
				process->program_counter + ((*value).u_ind) % IDX_MOD);
	if (*type == e_reg || *type == e_ind)
		(*type) = e_result;
}

void		op_live(t_process *process, t_args *args)
{
	int32_t	arg;
	t_vm	*vm;

	(void)process;
	vm = get_vm(NULL);
	arg = args->value[0].u_dir32;
	if (arg > 0 && arg <= (int)vm->nb_champs)
	{
		vm->champions[arg - 1].live_counter++;
		vm->last_alive = &vm->champions[arg - 1];
		printf("\e[%dmPlayer %d (%s) is alive\e[0m\n", \
		31 + arg, arg, vm->champions[arg - 1].name);
	}
	else
		printf("unknown player %d is alive\n", arg);
}

void		op_ld(t_process *process, t_args *args)
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], LD);
	result = args->value[0].u_dir32;
	process->registers[args->value[1].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_st(t_process *process, t_args *args)
{
	int32_t	value_to_store;

	value_to_store = process->registers[args->value[0].u_reg];
	if (args->type[1] == e_ind)
		write4_memory(get_vm(NULL), value_to_store, \
		process->program_counter + (args->value[1].u_ind % IDX_MOD));
	else if (args->type[1] == e_reg)
		process->registers[args->value[1].u_reg] = value_to_store;
	process->carry = (value_to_store == 0) ? 1 : 0;
}

void		op_add(t_process *process, t_args *args)
{
	int32_t	result;

	result = process->registers[args->value[0].u_reg]
		+ process->registers[args->value[1].u_reg];
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}
