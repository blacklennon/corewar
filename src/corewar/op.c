/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/16 16:27:07 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

#include "corewar.h"

static void	get_value_of_arg(t_process *process, t_int_types *value, t_int_types_enum *type)
{
	if (*type == e_reg) 
	{
		(*value).u_dir32 = process->registers[(*value).u_reg];
		*type = e_dir;
	}
	else if (*type == e_ind)
	{
		(*value).u_dir32 = read4_memory(get_vm(NULL), (*value).u_ind);
		*type = e_dir;
	}
}

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
		printf("player %d is alive\n", arg);
	}
	else
		printf("unknown player %d is alive\n", arg);
}

void		op_ld(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
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

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	get_value_of_arg(process, &args->value[1], &args->type[1]);
	printf(" value 0 : %x value 1 = %x\n", args->value[0].u_dir32, args->value[1].u_dir32);
	result = args->value[0].u_dir32 & args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	printf(" result : %x\n", process->registers[args->value[2].u_dir32]);
	printf(" result : %x\n", result);
}

void		op_or(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	get_value_of_arg(process, &args->value[1], &args->type[1]);
	printf(" value 0 : %x value 1 = %x\n", args->value[0].u_dir32, args->value[1].u_dir32);
	result = args->value[0].u_dir32 | args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	printf(" result : %x\n", process->registers[args->value[2].u_dir32]);
	printf(" result : %x\n", result);
	process->carry = (result == 0) ? 1 : 0;
}

void		op_xor(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	get_value_of_arg(process, &args->value[1], &args->type[1]);
	printf(" value 0 : %x value 1 = %x\n", args->value[0].u_dir32, args->value[1].u_dir32);
	result = args->value[0].u_dir32 ^ args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	printf(" result : %x\n", process->registers[args->value[2].u_dir32]);
	printf(" result : %x\n", result);
	process->carry = (result == 0) ? 1 : 0;
}

void		op_zjmp(t_process *process, t_args *args) // OK
{
	if (process->carry == 1)
		process->program_counter += args->value[0].u_dir16 - 3;
}

int		if_registre(int value, t_process *process, int byte)
{
	t_vm *vm;

	vm = get_vm(NULL);
	value = ((vm->memory[(process->program_counter + 1) % MEM_SIZE] >> byte & 0x03) == 1) ?
		process->registers[value] : value;
	return (value);
}

void		op_ldi(t_process *process, t_args *args)
{
	int32_t	value;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	get_value_of_arg(process, &args->value[1], &args->type[1]);
//	address = process->program_counter + ((args->value[0].u_dir32 + args->value[1].u_dir32) % IDX_MOD); // ou (all % IDX_MOD)
//	process->registers[args->value[2].u_reg] = read4_memory(get_vm(NULL), address); // pas write plutot?
	args->value[0] = if_registre(&args->value[0], process, 6);
	args->value[1] = if_registre(&args->value[1], process, 4);
	value = (&args->value[0] + &args->value[1]) % IDX_MOD;
	process->registers[args->value[2].u_reg] = value;
	process->carry = (process->registers[args->value[2].u_reg] == 0) ? 1 : 0; // ou value == 0
}

void		op_sti(t_process *process, t_args *args)
{
	int32_t	value_to_store; // est ce que ca serait un int8_t?
	int32_t address;

	value_to_store = process->registers[args->value[0].u_reg];
	get_value_of_arg(process, &args->value[1], &args->type[1]);
	get_value_of_arg(process, &args->value[2], &args->type[2]);
	args->value[1] = if_registre(&args->value[1], process, 4);
	args->value[2] = if_registre(&args->value[2], process, 2);
	address = (&args->value[1] + &args->value[2]) % IDX_MOD;
	write4_memory(get_vm(NULL), value_to_store, process->program_counter + address);
	process->carry = (value_to_store == 0) ? 1 : 0;
}

void		op_aff(t_process *process, t_args *args)
{
	//uint8_t	ocp;

	// (void)args;
	// ocp = vm->memory[++process->program_counter % MEM_SIZE];
	// if (ocp != 0x40)
	// 	//crash ?
	// ocp = vm->memory[++process->program_counter % MEM_SIZE];
	// if (ocp > 0 && ocp <= REG_NUMBER)
	//printf("process %s is saying `%c'\n", process->name, process->registers[ocp - 1] % 256);
	(void)process;
	(void)args;
	printf("hello world\n");
}
