/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:06:58 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/12 14:37:37 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// debug
#include <stdio.h>

#include <stddef.h>
#include "corewar.h"

static int		read_ocp(t_op *op, uint8_t ocp, t_arguments *args)
{
	t_int_types_enum	*tmp2;
	uint8_t				mask;
	uint8_t				tmp;
	int					i;

	mask = 0xc0;
	i = 0;
	while (i++ < op->nb_params)
	{
		tmp = 0;
		tmp = (tmp & mask) >> (4 - i) * 2;
		if (tmp == REG_CODE && (op->params[i - 1] & T_REG) != 0)
			*tmp2 = int_8;
		else if (tmp == IND_CODE && (op->params[i - 1] & T_IND) != 0)
			*tmp2 = int_16;
		else if (tmp == DIR_CODE && (op->params[i - 1] & T_DIR) != 0)
			*tmp2 = op->little_dir == 1 ? int_16 : int_32;
		else
			return (0);
		mask >> 2;
		//TODO find a way to iterate through argument types
	}
	return (1);
}

static void		do_op(t_process *process, t_vm *vm)
{
	uint8_t		ocp;
	t_op		*op;
	t_arguments	args;

	op = &op_tab[vm->memory[process->program_counter]];
	if (op->ocp == 1)
	{
		ocp = vm->memory[(process->program_counter + 1) % MEM_SIZE];
		if (read_ocp(op, ocp, &args) == 0)
			crash(process, "bad_ocp");
	}
	op->op_func(process, vm);
}

void			launch(t_vm *vm)
{
	size_t		i;

	while (42)
	{
		//printf("cycle: %zu\n", vm->cycle);
		if (vm->cycle == 500)
			break ;
		i = 0;
		while (i < vm->nb_champs)
		{
			if (vm->process[i].next_op == vm->cycle)
				do_op(&vm->process[i], vm);
			vm->process[i++].program_counter %= MEM_SIZE;
		}
		vm->cycle++;
	}
}