/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:30:17 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/26 19:31:13 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_sub(t_process *process, t_args *args)
{
	int32_t	result;

	result = process->registers[args->value[0].u_reg]
		- process->registers[args->value[1].u_reg];
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_and(t_process *process, t_args *args)
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], AND);
	get_value_of_arg(process, &args->value[1], &args->type[1], AND);
	result = args->value[0].u_dir32 & args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_or(t_process *process, t_args *args)
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], OR);
	get_value_of_arg(process, &args->value[1], &args->type[1], OR);
	result = args->value[0].u_dir32 | args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_xor(t_process *process, t_args *args)
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], XOR);
	get_value_of_arg(process, &args->value[1], &args->type[1], XOR);
	result = args->value[0].u_dir32 ^ args->value[1].u_dir32;
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_zjmp(t_process *process, t_args *args)
{
	if (process->carry == 1)
		process->program_counter += args->value[0].u_dir16;
}
