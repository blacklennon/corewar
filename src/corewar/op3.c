/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:32:03 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/26 19:58:53 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "corewar.h"

void		op_lldi(t_process *process, t_args *args)
{
	int32_t	value;
	int32_t	address;

	address = 0;
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
		crash(process, "This should never been reached op3.c:31");
	value = read4_memory(get_vm(NULL), process->program_counter + address);
	process->registers[args->value[2].u_reg] = value;
	process->carry = (value == 0) ? 1 : 0;
}

void		op_lld(t_process *process, t_args *args)
{
	int32_t	result;

	get_value_of_arg(process, &args->value[0], &args->type[0], LLD);
	result = args->value[0].u_dir32;
	process->registers[args->value[1].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
}

void		op_aff(t_process *process, t_args *args)
{
	char	value;

	value = (char)(process->registers[args->value[0].u_reg] % 256);
	ft_printf("Process %s is saying `%c'\n", process->champion->name, value);
	process->carry = (value == 0) ? 1 : 0;
}
