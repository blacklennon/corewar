/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:22:24 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/12 13:30:53 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	La fonction op_st va stocker la valeur trouvee dans un registre
**	si la destination est un indirect, on stocke la valeur dans la vm
**	via le modulo IDX_MOD qui en limite la portee
**	si la destination est un registre
**	on met la valeur a stocker dans ce registre
*/

void		op_st(t_process *process, t_args *args)
{
	int32_t	value_to_store;
	t_vm	*vm;

	vm = get_vm(NULL);
	value_to_store = process->registers[args->value[0].u_reg];
	if (args->type[1] == e_ind)
	{
		write4_memory(get_vm(NULL), value_to_store,\
		process->program_counter + (args->value[1].u_ind % IDX_MOD));
		if (vm->verbose == 3)
			ft_printf("Value of ST : %d loaded in memory at %d\n",\
				value_to_store, process->program_counter\
					+ (args->value[1].u_ind % IDX_MOD));
	}
	else if (args->type[1] == e_reg)
	{
		process->registers[args->value[1].u_reg] = value_to_store;
		if (vm->verbose == 3)
			ft_printf("Value of ST : %d loaded in reg %d\n",\
				value_to_store, args->value[1].u_reg);
	}
	process->carry = (value_to_store == 0) ? 1 : 0;
}

/*
**	STI reste a commenter et a appliquer le verbose
*/

void		op_sti(t_process *process, t_args *args)
{
	int32_t	value_to_store;
	int32_t	address;

	address = 0;
	value_to_store = process->registers[args->value[0].u_reg];
	get_value_of_arg(process, &args->value[1], &args->type[1], STI);
	get_value_of_arg(process, &args->value[2], &args->type[2], STI);
	if (args->type[1] == e_result && args->type[2] == e_dir)
		address = args->value[1].u_dir32 + args->value[2].u_dir16;
	else if (args->type[1] == e_result && args->type[2] == e_result)
		address = args->value[1].u_dir32 + args->value[2].u_dir32;
	else if (args->type[1] == e_dir && args->type[2] == e_dir)
		address = args->value[1].u_dir16 + args->value[2].u_dir16;
	else if (args->type[1] == e_dir && args->type[2] == e_result)
		address = args->value[1].u_dir16 + args->value[2].u_dir32;
	else
		crash(process, "This should never been reached op2.c:67");
	write4_memory(get_vm(NULL), value_to_store, \
	process->program_counter + (address % IDX_MOD));
	process->carry = (value_to_store == 0) ? 1 : 0;
}
