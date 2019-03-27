/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_05a_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:21:51 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/27 18:41:24 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include "corewar.h"

void		get_value_of_arg(t_process *process, t_int_types *value, \
			t_int_types_enum *type, int opcode)
{
	if (*type == e_reg)
		(*value).u_dir32 = process->registers[(*value).u_reg];
	else if (*type == e_ind && (opcode == LLD || opcode == LLDI))
		(*value).u_dir32 = read4_memory(get_vm(NULL), \
				process->program_counter + (*value).u_ind);
	else if (*type == e_ind)
		(*value).u_dir32 = read4_memory(get_vm(NULL), \
				process->program_counter + ((*value).u_ind) % IDX_MOD);
	if (*type == e_reg || *type == e_ind)
		(*type) = e_result;
}

/*
**	La fonction op_live va dire qu un joueur est en vie
**	on prend les 4 octets qui suivent l opcode live
**	et on declare ce champion comme etant en vie
**	Si le numero de joueur n existe pas, le live est compte,
**	mais n est utile pour aucun joueur
*/

void		op_live(t_process *process, t_args *args)
{
	int32_t	arg;
	t_vm	*vm;

	(void)process;
	vm = get_vm(NULL);
	arg = args->value[0].u_dir32;
	if (arg > 0 && arg <= (int)vm->nb_champs)
	{
		vm->champions[arg - 1].live_counter++;
		vm->last_alive = &vm->champions[arg - 1];
		if (vm->verbose >= 1)
			ft_printf("\e[%dmPlayer %d (%s) is alive\e[0m\n", \
		31 + arg, arg, vm->champions[arg - 1].name);
	}
	else
	{
		if (vm->verbose >= 1)
			ft_printf("unknown player %d is alive\n", arg);
	}
}

/*
**	La fonction op_ld va charger la valeur trouvee dans la vm via un dir32
**	ou dans un indirect de 16
**	cette valeur est chargee dans le registre de destination
*/

void		op_ld(t_process *process, t_args *args)
{
	int32_t	result;
	t_vm	*vm;

	vm = get_vm(NULL);
	get_value_of_arg(process, &args->value[0], &args->type[0], LD);
	result = args->value[0].u_dir32;
	process->registers[args->value[1].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	if (vm->verbose == 3)
		ft_printf("Value of LD : %d loaded in reg %d\n",\
			result, args->value[1].u_reg);
}

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
	t_vm 	*vm;

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
**	La fonction op_add realise une addition entre deux valeurs
**	et charge le resultat dans un registre
**	ces valeurs sont forcement dans des registres
*/

void		op_add(t_process *process, t_args *args)
{
	int32_t	result;
	t_vm	*vm;

	vm = get_vm(NULL);
	result = process->registers[args->value[0].u_reg]\
		+ process->registers[args->value[1].u_reg];
	process->registers[args->value[2].u_reg] = result;
	process->carry = (result == 0) ? 1 : 0;
	if (vm->verbose == 3)
	{
		ft_printf("Value is %d, (%d + %d), stored in reg %d\n", result,\
			process->registers[args->value[0].u_reg],\
			process->registers[args->value[1].u_reg], args->value[2].u_reg);
	}
}
