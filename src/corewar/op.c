/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/20 03:20:38 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

#include "corewar.h"

static void	get_value_of_arg(t_process *process, t_int_types *value, t_int_types_enum *type) // ajouter t_op pour dir16/32 et indirect valeur ou address
{
	if (*type == e_reg) 
	{
		(*value).u_dir32 = process->registers[(*value).u_reg];
		*type = e_dir;
	}
	else if (*type == e_ind)
	{
		(*value).u_dir32 = read4_memory(get_vm(NULL), process->program_counter + ((*value).u_ind) % IDX_MOD);
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

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	get_value_of_arg(process, &args->value[1], &args->type[1]);
	result = args->value[0].u_dir32 & args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	printf("AND: %x & %x = %x\n", args->value[0].u_dir32, args->value[1].u_dir32, result);
}

void		op_or(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	get_value_of_arg(process, &args->value[1], &args->type[1]);
	result = args->value[0].u_dir32 | args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	printf(" OR: %x | %x = %x\n", args->value[0].u_dir32, args->value[1].u_dir32, result);
}

void		op_xor(t_process *process, t_args *args) // OK
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	get_value_of_arg(process, &args->value[1], &args->type[1]);
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
/* OLD
int32_t		if_registre(int32_t value, t_process *process, int byte)
{
	t_vm *vm;

	vm = get_vm(NULL);
	value = ((vm->memory[(process->program_counter + 1) % MEM_SIZE] >> byte & 0x03) == 1) ?
		process->registers[value] : value;
	return (value);
}
*/
void		op_ldi(t_process *process, t_args *args)
{
	int32_t	value;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	get_value_of_arg(process, &args->value[1], &args->type[1]);
//	address = process->program_counter + ((args->value[0].u_dir32 + args->value[1].u_dir32) % IDX_MOD); // ou (all % IDX_MOD)
//	process->registers[args->value[2].u_reg] = read4_memory(get_vm(NULL), address); // pas write plutot?
	args->value[0].u_dir32 = (args->type[0] == e_reg) ? 
		process->registers[args->value[0].u_reg] : args->value[0].u_dir32; // atention le arg0 peut etre un indirect
	args->value[1].u_dir32 = (args->type[1] == e_reg) ?
		process->registers[args->value[1].u_reg] : args->value[1].u_dir32;
	value = (args->value[0].u_dir32 + args->value[1].u_dir32) % IDX_MOD; // j ai mis u_dir32 a chaque pour eviter les erreurs de compil a voir si c est juste
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
	args->value[1].u_dir32 = (args->type[1] == e_reg) ?
		process->registers[args->value[1].u_reg] : args->value[1].u_dir32; // atention arg1 peut etre un indirect
	args->value[2].u_dir32 = (args->type[2] == e_reg) ?
		process->registers[args->value[2].u_reg] : args->value[2].u_dir32;
	address = (args->value[1].u_dir32 + args->value[2].u_dir32) % IDX_MOD; // j ai mis u_dir32 a chaque pour eviter les erreurs de compil a voir si c est juste 
	write4_memory(get_vm(NULL), value_to_store, process->program_counter + address);
	process->carry = (value_to_store == 0) ? 1 : 0;
}

void		op_aff(t_process *process, t_args *args)
{
	printf("Process %s is saying `%c'\n", process->name, \
	process->registers[args->value[0].u_reg] % 256);
}

void		op_lld(t_process *process, t_args *args)
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	result = args->value[0].u_dir32;
	process->registers[args->value[1].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_lldi(t_process *process, t_args *args)
{
	int32_t	value;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	get_value_of_arg(process, &args->value[1], &args->type[1]);
	args->value[0].u_dir32 = (args->type[0] == e_reg) ?
		process->registers[args->value[0].u_reg] : args->value[0].u_dir32;  // atention arg0 peut etre un indirect
	args->value[1].u_dir32 = (args->type[1] == e_reg) ?
		process->registers[args->value[1].u_reg] : args->value[1].u_dir32;
	value = (args->value[0].u_dir32 + args->value[1].u_dir32);
	process->registers[args->value[2].u_reg] = value;
	process->carry = (process->registers[args->value[2].u_reg] == 0) ? 1 : 0; // ou value == 0
}

t_process	*ft_copy_process(t_process *process)
{
	t_process	*new_process;
	t_vm		*vm;

	vm = get_vm(NULL);
	if (!(new_process = (t_process *)ft_memalloc(sizeof(t_process))))
	{
		printf("erreur malloc copy process dans fork");
		return (NULL);
	}
	ft_memcpy(new_process, process, sizeof(t_process)); // faire un parcours des next jusqu a null pour copy le next;
	process->next = new_process; // il faut bien ajouter un process mais je ne sais pas si c est la bonne maniere de faire
	return (new_process);

}

void		op_fork(t_process *process, t_args *args)
{
	t_process 	*new_process;
	
	get_value_of_arg(process, &args->value[0], &args->type[0]);
	args->value[0].u_dir32 %= IDX_MOD;
	new_process = ft_copy_process(process);
	new_process->program_counter = (process->program_counter + args->value[0].u_dir32) % MEM_SIZE;
	if (new_process->program_counter < 0)
		new_process->program_counter += MEM_SIZE;
}

void		op_lfork(t_process *process, t_args *args)
{
	t_process *new_process;

	get_value_of_arg(process, &args->value[0], &args->type[0]);
	new_process = ft_copy_process(process);
	new_process->program_counter = (process->program_counter + args->value[0].u_dir32) % MEM_SIZE;
	if (new_process->program_counter < 0)
		new_process->program_counter += MEM_SIZE;
}
