/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/13 00:24:45 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

#include "corewar.h"

//WIP

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

void		live(t_process *process, t_vm *vm)
{
	int32_t	arg;

	arg = read4_memory(vm, ++process->program_counter);
	if (arg > 0 && arg <= (int)vm->nb_champs)
		vm->process[arg - 1].live_counter++;
	printf("player %d is alive\n", arg);
	process->program_counter += 4;
	process->next_op = vm->cycle + 10;
}

void		zjmp(t_process *process, t_vm *vm)
{
	int16_t	arg;

	arg = read2_memory(vm, process->program_counter + 1);
	if (process->carry == 1)
		process->program_counter += arg;
	else
		process->program_counter += 3;
	process->next_op = vm->cycle + 20;
}

void		aff(t_process *process, t_vm *vm)
{
	uint8_t	ocp;

	ocp = vm->memory[++process->program_counter % MEM_SIZE];
	if (ocp != 0x40)
		//crash ?
	ocp = vm->memory[++process->program_counter % MEM_SIZE];
	if (ocp > 0 && ocp <= REG_NUMBER)
		printf("process %s is saying `%c'\n", process->name, process->registers[ocp - 1] % 256);
	else
		//crash ?
	process->program_counter++;
	process->next_op = vm->cycle + 2;
}

// void		ld(t_process *process, t_vm *vm)
// {
// 	process->next_op = vm->cycle + 5;
// }