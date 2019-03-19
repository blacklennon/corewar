/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/16 17:53:59 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

#include "corewar.h"

int32_t			read4_memory(t_vm *vm, size_t index)
{
	int32_t		*tmp;
	uint8_t		tab[4];
	size_t		i;

	index %= MEM_SIZE;
	if (MEM_SIZE - index > 4)
		tmp = (int32_t*)&vm->memory[index];
	else
	{
		tmp = (int32_t*)tab;
		i = 0;
		ft_bzero(tab, sizeof(tab));
		while (i < 4)
		{
			tab[i] = vm->memory[index];
			index++;
			i++;
			index %= MEM_SIZE;
		}
	}
	return (swap_int32(*tmp));
}

int16_t			read2_memory(t_vm *vm, size_t index)
{
	int16_t		*tmp;
	uint8_t		tab[2];
	size_t		i;

	index %= MEM_SIZE;
	if (MEM_SIZE - index > 2)
		tmp = (int16_t*)&vm->memory[index];
	else
	{
		tmp = (int16_t*)tab;
		i = 0;
		ft_bzero(tab, sizeof(tab));
		while (i < 2)
		{
			tab[i] = vm->memory[index];
			index++;
			i++;
			index %= MEM_SIZE;
		}
	}
	return (swap_int16(*tmp));
}

void		write4_memory(t_vm *vm, int32_t value, size_t index)
{
	uint8_t		tab[4];
	size_t		i;

	*((int32_t*)tab) = swap_int32(value);
	i = 0;
	while (i < 4)
	{
		index %= MEM_SIZE;
		vm->memory[index] = tab[i];
		index++;
		i++;
	}
}

//jac 12032019
void		write2_memory(t_vm *vm, int16_t value, size_t index)
{
	uint8_t		tab[2];
	size_t		i;

	*((int16_t*)tab) = swap_int16(value);
	i = 0;
	while (i < 2)
	{
		index %= MEM_SIZE;
		vm->memory[index] = tab[i];
		index++;
		i++;
	}
}

void		op_live(t_process *process, t_args *args)
{
	int32_t	arg;
	t_vm	*vm;

	(void)process;
	vm = get_vm(NULL);
	arg = args->value[0].u_dir32;
	if (arg > 0 && arg <= (int)vm->nb_champs)
		vm->process[arg - 1].live_counter++;
	printf("player %d is alive\n", arg);
}

void		op_zjmp(t_process *process, t_args *args)
{
	if (process->carry == 1)
		process->program_counter += args->value[0].u_dir16 - 3;
}

void		op_aff(t_process *process, t_args *args)
{
	printf("Process %s is saying `%c'\n", process->name, \
	process->registers[args->value[0].u_reg] % 256);
}

void		op_add(t_process *process, t_args *args)
{
	int32_t	result;

	result = process->registers[args->value[0].u_reg]
		+ process->registers[args->value[1].u_reg];
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_sub(t_process *process, t_args *args)
{
	int32_t	result;

	result = process->registers[args->value[0].u_reg]
		- process->registers[args->value[1].u_reg];
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}
