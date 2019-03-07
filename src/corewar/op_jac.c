/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/06 15:33:58 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

#include "corewar.h"


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
/*
void		add(t_process *process, t_vm *vm)
{
	
}
*/
/*
void	add(t_process *prc, t_a *a)
{
	int	reg1;
	int	reg2;
	int	reg;

	if (!check_cycle(prc))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	reg1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	reg2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (!(reg == -1 || reg1 == -1 || reg2 == -1))
	{
		prc->reg[reg] = prc->reg[reg1] + prc->reg[reg2];
		prc->carry = (prc->reg[reg] == 0) ? 1 : 0;
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	sub(t_process *prc, t_a *a)
{
	int	reg1;
	int	reg2;
	int	reg;

	if (!check_cycle(prc))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	reg1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	reg2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (!(reg == -1 || reg1 == -1 || reg2 == -1))
	{
		prc->reg[reg] = prc->reg[reg1] - prc->reg[reg2];
		prc->carry = (prc->reg[reg] == 0) ? 1 : 0;
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	f_or(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	reg;

	if (!check_cycle(prc))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	v2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	v1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (!(((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1 && v2 == -1)
			|| ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1
				&& v1 == -1) || reg == -1))
	{
		v2 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
			prc->reg[v2] : v2;
		v1 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
			prc->reg[v1] : v1;
		prc->reg[reg] = v1 | v2;
		prc->carry = (prc->reg[reg] == 0) ? 1 : 0;
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	f_xor(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	reg;

	if (!check_cycle(prc))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	v2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	v1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (!(((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1 && v2 == -1)
			|| ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1
				&& v1 == -1) || reg == -1))
	{
		v2 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
			prc->reg[v2] : v2;
		v1 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
			prc->reg[v1] : v1;
		prc->reg[reg] = v1 ^ v2;
		prc->carry = (prc->reg[reg] == 0) ? 1 : 0;
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	f_and(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	reg;

	if (!check_cycle(prc))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	v2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	v1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (!(((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1 && v2 == -1)
			|| ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1
				&& v1 == -1) || reg == -1))
	{
		v2 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
			prc->reg[v2] : v2;
		v1 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
			prc->reg[v1] : v1;
		prc->reg[reg] = v1 & v2;
		prc->carry = (prc->reg[reg] == 0) ? 1 : 0;
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}
*/