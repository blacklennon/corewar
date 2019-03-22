/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/22 17:30:04 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "corewar.h"

static void	get_value_of_arg(t_process *process, t_int_types *value, t_int_types_enum *type, int opcode)
{
	if (*type == e_reg)
	{
		(*value).u_dir32 = process->registers[(*value).u_reg];
		*type = e_result;
	}
	else if (*type == e_ind && (opcode == LLD || opcode == LLDI))// sans restriction d adressage
	{
		(*value).u_dir32 = read4_memory(get_vm(NULL), process->program_counter + (*value).u_ind);
		*type = e_result;
	}
	else if (*type == e_ind)// avec restricition d adressage
	{
		(*value).u_dir32 = read4_memory(get_vm(NULL), process->program_counter + ((*value).u_ind) % IDX_MOD);
		*type = e_result;
	}
}//get value of args se trouve dans ld, and, or, xor, ldi, sti, lld, lldi, fork et lfork

void		op_live(t_process *process, t_args *args) // OK
{
	int32_t	arg;
	t_vm	*vm;

	(void)process;
	vm = get_vm(NULL);
	arg = args->value[0].u_dir32;
	if (arg > 0 && arg <= (int)vm->nb_champs)
	{
		vm->process[arg - 1].live_counter++;
		printf("\e[%dmPlayer %d (%s) is alive\e[0m\n", 31 + arg, arg, vm->process[arg - 1].name);
	}
	else
		printf("unknown player %d is alive\n", arg);
}

void		op_ld(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], LD);
	result = args->value[0].u_dir32;
	process->registers[args->value[1].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_st(t_process *process, t_args *args) // OK
{
	int32_t	value_to_store;

	value_to_store = process->registers[args->value[0].u_reg];
	if (args->type[1] == e_ind)
		write4_memory(get_vm(NULL), value_to_store, process->program_counter + (args->value[1].u_ind % IDX_MOD));
	else if (args->type[1] == e_reg)
		process->registers[args->value[1].u_reg] = value_to_store;
	process->carry = (value_to_store == 0) ? 1 : 0;
}

void		op_add(t_process *process, t_args *args) // OK
{
	int32_t	result;

	result = process->registers[args->value[0].u_reg]
		+ process->registers[args->value[1].u_reg];
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_sub(t_process *process, t_args *args) // OK
{
	int32_t	result;

	result = process->registers[args->value[0].u_reg]
		- process->registers[args->value[1].u_reg];
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_and(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], AND);
	get_value_of_arg(process, &args->value[1], &args->type[1], AND);
	result = args->value[0].u_dir32 & args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	printf("AND: %x & %x = %x\n", args->value[0].u_dir32, args->value[1].u_dir32, result);
}

void		op_or(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], OR);
	get_value_of_arg(process, &args->value[1], &args->type[1], OR);
	result = args->value[0].u_dir32 | args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	printf(" OR: %x | %x = %x\n", args->value[0].u_dir32, args->value[1].u_dir32, result);
}

void		op_xor(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], XOR);
	get_value_of_arg(process, &args->value[1], &args->type[1], XOR);
	result = args->value[0].u_dir32 ^ args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	printf("XOR: %x ^ %x = %x\n", args->value[0].u_dir32, args->value[1].u_dir32, result);
}

void		op_zjmp(t_process *process, t_args *args) // OK
{
	if (process->carry == 1)
		process->program_counter += args->value[0].u_dir16;
}

void		op_ldi(t_process *process, t_args *args)
{
	int32_t	value;
	int32_t	address;

	get_value_of_arg(process, &args->value[0], &args->type[0], LDI);
	get_value_of_arg(process, &args->value[1], &args->type[1], LDI);
	if (args->type[0] == e_result && args->type[1] != e_result)
		address = args->value[0].u_dir32 + args->value[1].u_dir16;
	else if (args->type[0] == e_result && args->type[1] == e_result)
		address = args->value[0].u_dir32 + args->value[1].u_dir32;
	else if (args->type[0] != e_result && args->type[1] != e_result)
		address = args->value[0].u_dir16 + args->value[1].u_dir16;
	else if (args->type[0] != e_result && args->type[1] == e_result)
		address = args->value[0].u_dir16 + args->value[1].u_dir32;
	else
	{
		address = 0;
		printf("NOOOOOOOOON\n");
	}
	value = read4_memory(get_vm(NULL), process->program_counter + (address % IDX_MOD)); // Probleme ici, valgrind retourne une erreur si on ne lit pas le bon type de parametre (udir16 ou udir32)
	process->registers[args->value[2].u_reg] = value;
	process->carry = (value == 0) ? 1 : 0;
}

void		op_sti(t_process *process, t_args *args)
{
	int32_t	value_to_store; // est ce que ca serait un int8_t?
	int32_t	address;

	value_to_store = process->registers[args->value[0].u_reg];
	get_value_of_arg(process, &args->value[1], &args->type[1], STI);
	get_value_of_arg(process, &args->value[2], &args->type[2], STI);
	if (args->type[1] == e_result && args->type[2] != e_result)
		address = args->value[1].u_dir32 + args->value[2].u_dir16;
	else if (args->type[1] == e_result && args->type[2] == e_result)
		address = args->value[1].u_dir32 + args->value[2].u_dir32;
	else if (args->type[1] != e_result && args->type[2] != e_result)
		address = args->value[1].u_dir16 + args->value[2].u_dir16;
	else if (args->type[1] != e_result && args->type[2] == e_result)
		address = args->value[1].u_dir16 + args->value[2].u_dir32;
	else
	{
		address = 0;
		printf("NOOOOOOOOON\n");
	}
	write4_memory(get_vm(NULL), value_to_store, process->program_counter + (address % IDX_MOD));
	process->carry = (value_to_store == 0) ? 1 : 0;
}

t_process	*fork_process(t_process *process)
{
	t_process	*new_process;

	if ((new_process = (t_process*)malloc(sizeof(t_process))) == NULL)
		crash(process, "fork failed :(");
	ft_memcpy(new_process, process, sizeof(t_process));
	return (new_process);
}

void		op_fork(t_process *process, t_args *args) // OK
{
	t_vm		*vm;
	t_process	*new_process;

	args->value[0].u_dir16 %= IDX_MOD;
	new_process = fork_process(process);
	new_process->program_counter = (process->program_counter + args->value[0].u_dir16) % MEM_SIZE;
	vm = get_vm(NULL);
	new_process->next = vm->forked_process;
	vm->forked_process = new_process;
}

void		op_lld(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], LLD);
	result = args->value[0].u_dir32;
	process->registers[args->value[1].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_lldi(t_process *process, t_args *args)
{
	int32_t	value;
	int32_t	address;

	get_value_of_arg(process, &args->value[0], &args->type[0], LLDI);
	get_value_of_arg(process, &args->value[1], &args->type[1], LLDI);
	if (args->type[0] == e_result && args->type[1] != e_result)
		address = args->value[0].u_dir32 + args->value[1].u_dir16;
	else if (args->type[0] == e_result && args->type[1] == e_result)
		address = args->value[0].u_dir32 + args->value[1].u_dir32;
	else if (args->type[0] != e_result && args->type[1] != e_result)
		address = args->value[0].u_dir16 + args->value[1].u_dir16;
	else if (args->type[0] != e_result && args->type[1] == e_result)
		address = args->value[0].u_dir16 + args->value[1].u_dir32;
	else
	{
		address = 0;
		printf("NOOOOOOOOON\n");
	}
	value = read4_memory(get_vm(NULL), process->program_counter + address);
	process->registers[args->value[2].u_reg] = value;
	process->carry = (value == 0) ? 1 : 0;
}

void		op_lfork(t_process *process, t_args *args) // OK
{
	t_vm		*vm;
	t_process	*new_process;

	new_process = fork_process(process);
	new_process->program_counter = (process->program_counter + args->value[0].u_dir16) % MEM_SIZE;
	vm = get_vm(NULL);
	new_process->next = vm->forked_process;
	vm->forked_process = new_process;
}

void		op_aff(t_process *process, t_args *args) // OK
{
	int32_t	value;
	
	value = process->registers[args->value[0].u_reg] % 256;
	printf("Process %s is saying `%c'\n", process->name, value);
	process->carry = (value == 0) ? 1 : 0;
}